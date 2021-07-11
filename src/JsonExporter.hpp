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

    static std::string arrayToJson(uint8_t array[], uint size) {
        uint u_array[size];
        for (uint i = 0; i < size; i++) {
            u_array[i] = array[i];
        }
        return arrayToJson(u_array, size);
    }

    template <typename T> static std::string arrayToJson(T array[], uint size) {
        std::ostringstream ss;

        ss << arrayCharBegin << array[0];

        for (uint i = 1; i < size;) {
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

    template <class T>
    static std::string
    treeToJson(T &tree, const typename T::_DataClass::sampleScaler
                            scalers[T::_DataClass::N_Attributes] = NULL) {

        typedef typename T::_NodeClass NodeClass;
        typedef typename T::_NodeClass::node_index_t node_index_t;
        typedef typename T::_NodeClass::class_index_t class_index_t;

        std::map<node_index_t, NodeClass &> nodeMap;

        auto fn = [&nodeMap](NodeClass &node, node_index_t nodeID) {
            nodeMap.insert(std::pair<node_index_t, NodeClass &>(nodeID, node));
        };

        DFS(tree, tree.getRootNode(), fn);
        std::map<node_index_t, std::pair<std::string, std::string>>
            &nodeDataMap =
                nodesToJson(tree, nodeMap, T::_DataClass::N_Classes, scalers);

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

        class_index_t classRange[T::_DataClass::N_Classes];
        for (class_index_t i = 0; i < T::_DataClass::N_Classes; i++) {
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

        delete &nodeDataMap;

        return mapToJson(json);
    }

    template <class T>
    static std::map<typename T::_NodeClass::node_index_t,
                    std::pair<std::string, std::string>> &
    nodesToJson(
        T &tree,
        std::map<typename T::_NodeClass::node_index_t, typename T::_NodeClass &>
            nodeMap,
        typename T::_NodeClass::class_index_t nClasses,
        const typename T::_DataClass::sampleScaler
            scalers[T::_DataClass::N_Attributes] = NULL) {

        typedef typename T::_NodeClass _NodeClass;
        typedef typename T::_NodeClass::node_index_t node_index_t;

        std::map<node_index_t, std::pair<std::string, std::string>>
            *nodeDataMap =
                new std::map<node_index_t, std::pair<std::string, std::string>>;

        for (auto &pair : nodeMap) {
            node_index_t nodeID = pair.first;
            _NodeClass &node = pair.second;

            node_index_t leftChildID = 0, rightChildID = 0;

            for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
                node_index_t innerNodeID = it->first;
                _NodeClass &innerNode = it->second;

                if (&tree.getNode(node.getLeftChild()) == &innerNode) {
                    leftChildID = innerNodeID;
                } else if (&tree.getNode(node.getRightChild()) == &innerNode) {
                    rightChildID = innerNodeID;
                }
            }

            nodeDataMap->insert(
                std::pair<node_index_t, std::pair<std::string, std::string>>(
                    nodeID, std::pair<std::string, std::string>(
                                nodeDataToJson(node, leftChildID, rightChildID,
                                               scalers),
                                nodeClassCountsToJson(node, nClasses))));
        }

        return *nodeDataMap;
    }

    template <class T>
    static std::string nodeClassCountsToJson(T &node, uint nClasses) {
        typedef typename T::class_index_t class_index_t;

        std::string array[nClasses];

        for (class_index_t i = 0; i < nClasses; i++) {
            array[i] =
                std::to_string(node.getData().getSampleCountPerClass(i)) + ".0";
        }

        const std::string intermediateArray[1] = {arrayToJson(array, nClasses)};
        return arrayToJson(intermediateArray, 1);
    }

    template <class T>
    static std::string
    nodeDataToJson(T &node, typename T::node_index_t leftChildID,
                   typename T::node_index_t rightChildID,
                   const typename T::_DataClass::sampleScaler
                       scalers[T::_DataClass::N_Attributes] = NULL) {

        const std::string array[7] = {
            node.hasLeftChild() ? std::to_string(leftChildID) : "-1",
            node.hasRightChild() ? std::to_string(rightChildID) : "-1",
            node.isSplit() ? std::to_string(node.getSplitAttributeIndex())
                           : "-2",
            node.isSplit()
                ? std::to_string(scalers != NULL
                                     ? scalers[node.getSplitAttributeIndex()](
                                           node.getSplitValue())
                                     : node.getSplitValue())
                : "-2.0",
            std::to_string(node.getData().getImpurity()),
            std::to_string(node.getData().getSampleCountTotal()),
            std::to_string(node.getData().getSampleCountTotal()) + ".0"};

        return arrayToJson(array, 7);
    }

    template <class T, class fn_T>
    static void DFS(T &tree, typename T::_NodeClass &node, fn_T function) {
        typename T::_NodeClass::node_index_t c = 0;
        _DFS_handle(tree, node, function, c);
    }

    template <class T>
    static void copyNode(T &oldTree, T &newTree, typename T::_NodeClass &node,
                         typename T::_NodeClass &newNode) {

        if (node.isSplit()) {
            newTree.splitNode(newNode, node.getSplitAttributeIndex(),
                              node.getSplitValue());
        }

        if (node.hasLeftChild()) {
            copyNode(oldTree, newTree, oldTree.getNode(node.getLeftChild()),
                     newTree.getNode(newNode.getLeftChild()));
        }
        if (node.hasRightChild()) {
            copyNode(oldTree, newTree, oldTree.getNode(node.getRightChild()),
                     newTree.getNode(newNode.getRightChild()));
        }
    }

    template <class T>
    static void
    inferDataset(T &tree,
                 typename T::_NodeClass::_DataClass::data_t
                     dataset[][T::_NodeClass::_DataClass::N_Attributes + 1],
                 uint datasetSize) {
        for (uint i = 0; i < datasetSize; i++) {
            typename T::node_index_t nodeIndex = tree.getRootNodeIndex();

            do {
                nodeIndex = tree.getNode(nodeIndex).sortSample(dataset[i]);
                tree.getNode(nodeIndex).getData().update(
                    dataset[i],
                    dataset[i][T::_NodeClass::_DataClass::N_Attributes]);

            } while (nodeIndex != 0);
        }
    }

    template <class T>
    static void
    inferDataset(T &tree,
                 typename T::_NodeClass::_DataClass::data_t
                     dataset[][T::_NodeClass::_DataClass::N_Attributes],
                 typename T::_NodeClass::class_index_t classif[],
                 uint datasetSize) {
        for (uint i = 0; i < datasetSize; i++) {
            typename T::node_index_t nodeIndex = tree.getRootNodeIndex();

            do {
                nodeIndex = tree.getNode(nodeIndex).sortSample(dataset[i]);
                tree.getNode(nodeIndex).getData().update(dataset[i],
                                                         classif[i]);
            } while (nodeIndex != 0);
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
    static void _DFS_handle(T &tree, typename T::_NodeClass &node,
                            fn_T function,
                            typename T::_NodeClass::node_index_t &nodeCounter) {

        function(node, nodeCounter++);

        if (node.hasLeftChild()) {
            _DFS_handle(tree, tree.getNode(node.getLeftChild()), function,
                        nodeCounter);
        }
        if (node.hasRightChild()) {
            _DFS_handle(tree, tree.getNode(node.getRightChild()), function,
                        nodeCounter);
        }
    }
};

#endif
