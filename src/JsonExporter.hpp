#ifndef __JSON_EXPORTER_HPP__
#define __JSON_EXPORTER_HPP__

#include "Node.hpp"
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include <iostream>

class JsonExporter {
  public:
    JsonExporter() {}

    template <typename T> static std::string arrayToJson(T array[], uint size) {
        std::ostringstream ss;

        ss << arrayCharBegin << array[0];
        uint i = 1;

        while (i < size) {
            ss << arrayCharDelimiter << array[i++];
        }

        ss << arrayCharEnd;
        return ss.str();
    }

    template <typename T> static std::string vectorToJson(std::vector<T> v) {
        std::ostringstream ss;
        ss << arrayCharBegin;

        for (auto &elem : v) {
            ss << elem;
            if (v.back() != elem) {
                ss << arrayCharDelimiter;
            }
        }

        ss << arrayCharEnd;
        return ss.str();
    }

    template <typename T>
    static std::string mapToJson(std::map<std::string, T> map) {
        std::ostringstream ss;
        ss << objCharBegin;
        std::string lastKey = (--map.end())->first;

        for (auto &pair : map) {
            ss << "\"" << pair.first << "\":" << pair.second;
            if (!lastKey.compare(pair.first)) {
                continue;
            }
            ss << objCharDelimiter;
        }

        ss << objCharEnd;
        return ss.str();
    }

    template <class T> static std::string treeToJson(T tree, uint nClasses) {

        typedef typename T::_NodeClass NodeClass;

        std::map<uint, NodeClass *> nodeMap;

        auto fn = [&nodeMap](NodeClass *node, uint nodeID) {
            nodeMap.insert(std::pair<uint, NodeClass *>(nodeID, node));
        };

        DFS(tree.getRootNode(), fn);
        std::map<uint, std::pair<std::string, std::string>> nodeDataMap =
            nodesToJson(nodeMap, nClasses);

        std::vector<std::string> nodes;
        std::vector<std::string> values;

        for (auto &pair : nodeDataMap) {
            nodes.push_back(pair.second.first);
            values.push_back(pair.second.second);
        }

        std::cout << "Nodes: " << vectorToJson(nodes) << std::endl;
        std::cout << "Values: " << vectorToJson(values) << std::endl;

        return "";
    }

    template <class T>
    static std::map<uint, std::pair<std::string, std::string>> &
    nodesToJson(std::map<uint, T *> nodeMap, uint nClasses) {

        std::map<uint, std::pair<std::string, std::string>> *nodeDataMap =
            new std::map<uint, std::pair<std::string, std::string>>;

        for (auto &pair : nodeMap) {
            uint nodeID = pair.first;
            T *node = pair.second;

            uint leftChildID = 0, rightChildID = 0;

            for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
                uint innerNodeID = it->first;
                T *innerNode = it->second;

                if (node->getLeftChild() == innerNode) {
                    leftChildID = innerNodeID;
                } else if (node->getRightChild() == innerNode) {
                    rightChildID = innerNodeID;
                }
            }

            nodeDataMap->insert(
                std::pair<uint, std::pair<std::string, std::string>>(
                    nodeID, std::pair<std::string, std::string>(
                                nodeDataToJson(node, leftChildID, rightChildID),
                                nodeClassCountsToJson(node, nClasses))));
        }

        return *nodeDataMap;
    }

    template <class T>
    static std::string nodeClassCountsToJson(T node, uint nClasses) {
        uint array[nClasses];

        for (uint i = 0; i < nClasses; i++) {
            array[i] = node->getData().getSampleCountPerClass(i);
        }

        const std::string intermediateArray[1] = {arrayToJson(array, nClasses)};
        return arrayToJson(intermediateArray, 1);
    }

    template <class T>
    static std::string nodeDataToJson(T *node, uint leftChildID,
                                      uint rightChildID) {

        typedef typename T::datatype datatype;

        const datatype array[7] = {
            node->hasLeftChild() ? datatype(leftChildID) : -1,
            node->hasRightChild() ? datatype(rightChildID) : -1,
            node->isSplit() ? datatype(node->getSplitAttributeIndex()) : -2,
            node->isSplit() ? node->getSplitValue() : -2,
            node->getData().getImpurity(),
            datatype(node->getData().getSampleCountTotal()),
            datatype(node->getData().getSampleCountTotal())};

        return arrayToJson(array, 7);
    }

    template <class T, class fn_T> static void DFS(T *node, fn_T function) {
        uint c = 0;
        _DFS_handle(node, function, c);
    }

  protected:
    static const char arrayCharBegin = '[';
    static const char arrayCharEnd = ']';
    static const char arrayCharDelimiter = ',';

    static const char objCharBegin = '{';
    static const char objCharEnd = '}';
    static const char objCharDelimiter = ',';

    const std::string dtypes =
        "[\"<i8\",\"<i8\",\"<i8\",\"<f8\",\"<f8\",\"<i8\",\"<f8\"]";

    const std::string params =
        "{\"ccp_alpha\": 0.0,\"class_weight\": null,\"criterion\": "
        "\"gini\",\"max_depth\": null,\"max_features\": "
        "null,\"max_leaf_nodes\": null,\"min_impurity_decrease\": "
        "0.0,\"min_impurity_split\": null,\"min_samples_leaf\": "
        "1,\"min_samples_split\": 2,\"min_weight_fraction_leaf\": "
        "0.0,\"random_state\": null,\"splitter\": \"best\"}";

    template <class T, class fn_T>
    static void _DFS_handle(T *node, fn_T function, uint &nodeCounter) {

        function(node, nodeCounter++);

        if (node->hasLeftChild()) {
            _DFS_handle(node->getLeftChild(), function, nodeCounter);
        }
        if (node->hasRightChild()) {
            _DFS_handle(node->getRightChild(), function, nodeCounter);
        }
    }
};

#endif
