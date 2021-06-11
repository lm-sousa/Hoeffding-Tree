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

    template <class T> static std::string treeToJson(T &tree) {

        typedef typename T::_NodeClass NodeClass;

        std::map<uint, NodeClass *> nodeMap;

        auto fn = [&nodeMap](NodeClass *node, uint nodeID) {
            nodeMap.insert(std::pair<uint, NodeClass *>(nodeID, node));
        };

        DFS(tree.getRootNode(), fn);
        std::map<uint, std::pair<std::string, std::string>> nodeDataMap =
            nodesToJson(nodeMap, T::_DataClass::N_Classes);

        std::vector<std::string> nodes;
        std::vector<std::string> values;

        for (auto &pair : nodeDataMap) {
            nodes.push_back(pair.second.first);
            values.push_back(pair.second.second);
        }

        std::map<std::string, std::string> tree_;

        tree_.insert(std::pair<std::string, std::string>(
            "max_depth", std::to_string(nodeMap.size())));
        tree_.insert(std::pair<std::string, std::string>(
            "node_count", std::to_string(nodeMap.size())));
        tree_.insert(
            std::pair<std::string, std::string>("nodes", vectorToJson(nodes)));
        tree_.insert(std::pair<std::string, std::string>("values",
                                                         vectorToJson(values)));
        tree_.insert(std::pair<std::string, std::string>(
            std::string("nodes_dtype"), dtypes));

        std::string jsonTree_ = mapToJson(tree_);

        std::map<std::string, std::string> json;

        uint classRange[T::_DataClass::N_Classes];
        for (uint i = 0; i < T::_DataClass::N_Classes; i++) {
            classRange[i] = i;
        }

        uint featureImportances[T::_DataClass::N_Attributes] = {0};
        /*for (uint i = 0; i < T::_DataClass::N_Attributes; i++) {
            featureImportances[i] = 0;
        }*/

        json.insert(
            std::pair<std::string, std::string>("meta", "\"decision-tree\""));
        json.insert(std::pair<std::string, std::string>(
            "feature_importances_",
            arrayToJson(featureImportances, T::_DataClass::N_Attributes)));
        json.insert(std::pair<std::string, std::string>(
            "max_features_", std::to_string(T::_DataClass::N_Attributes)));
        json.insert(std::pair<std::string, std::string>(
            "n_classes_", std::to_string(T::_DataClass::N_Classes)));
        json.insert(std::pair<std::string, std::string>(
            "n_features_", std::to_string(T::_DataClass::N_Attributes)));
        json.insert(std::pair<std::string, std::string>("n_outputs_", "1"));
        json.insert(std::pair<std::string, std::string>("tree_", jsonTree_));
        json.insert(std::pair<std::string, std::string>(
            "classes_", arrayToJson(classRange, T::_DataClass::N_Classes)));
        json.insert(std::pair<std::string, std::string>("params", params));

        return mapToJson(json);
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
        std::string array[nClasses];

        for (uint i = 0; i < nClasses; i++) {
            array[i] =
                std::to_string(node->getData().getSampleCountPerClass(i)) +
                ".0";
        }

        const std::string intermediateArray[1] = {arrayToJson(array, nClasses)};
        return arrayToJson(intermediateArray, 1);
    }

    template <class T>
    static std::string nodeDataToJson(T *node, uint leftChildID,
                                      uint rightChildID) {

        const std::string array[7] = {
            node->hasLeftChild() ? std::to_string(leftChildID) : "-1",
            node->hasRightChild() ? std::to_string(rightChildID) : "-1",
            node->isSplit() ? std::to_string(node->getSplitAttributeIndex())
                            : "-2",
            node->isSplit() ? std::to_string(node->getSplitValue() * 8)
                            : "-2.0",
            std::to_string(node->getData().getImpurity()),
            std::to_string(node->getData().getSampleCountTotal()),
            std::to_string(node->getData().getSampleCountTotal()) + ".0"};

        return arrayToJson(array, 7);
    }

    template <class T, class fn_T> static void DFS(T *node, fn_T function) {
        uint c = 0;
        _DFS_handle(node, function, c);
    }

    template <class T>
    static void copyNode(T &newTree, typename T::_NodeClass *node,
                         typename T::_NodeClass *newNode) {

        if (node->isSplit()) {
            newTree.splitNode(newNode, node->getSplitAttributeIndex(),
                              node->getSplitValue());
        }

        if (node->hasLeftChild()) {
            copyNode(newTree, node->getLeftChild(), newNode->getLeftChild());
        }
        if (node->hasRightChild()) {
            copyNode(newTree, node->getRightChild(), newNode->getRightChild());
        }
    }

  protected:
    static const char arrayCharBegin = '[';
    static const char arrayCharEnd = ']';
    static const char arrayCharDelimiter = ',';

    static const char objCharBegin = '{';
    static const char objCharEnd = '}';
    static const char objCharDelimiter = ',';

    static const std::string dtypes;
    static const std::string params;

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
