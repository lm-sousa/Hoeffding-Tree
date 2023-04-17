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

        for (std::size_t i = 0; i < v.size(); i++) {

            ss << v.at(i);
            if (i != v.size() - 1) {
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

        typedef typename T::node_index_t node_index_t;
        typedef typename T::class_index_t class_index_t;

        std::map<node_index_t, node_index_t> nodeMap;

        auto fn = [&nodeMap](node_index_t nodeIndex, node_index_t nodeID) {
            nodeMap.insert(
                std::pair<node_index_t, node_index_t>(nodeID, nodeIndex));
        };

        DFS(tree, tree.getRootNodeIndex(), fn);
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
    static std::map<typename T::node_index_t,
                    std::pair<std::string, std::string>> &
    nodesToJson(
        T &tree,
        std::map<typename T::node_index_t, typename T::node_index_t> nodeMap,
        typename T::class_index_t nClasses,
        const typename T::_DataClass::sampleScaler
            scalers[T::_DataClass::N_Attributes] = NULL) {

        typedef typename T::node_index_t node_index_t;

        std::map<node_index_t, std::pair<std::string, std::string>>
            *nodeDataMap =
                new std::map<node_index_t, std::pair<std::string, std::string>>;

        for (auto &pair : nodeMap) {
            node_index_t nodeID = pair.first;
            node_index_t nodeIndex = pair.second;

            node_index_t leftChildID = 0, rightChildID = 0;

            for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
                node_index_t innerNodeID = it->first;
                node_index_t innerNode = it->second;

                if (tree.getLeftChildOfNode(nodeIndex) == innerNode) {
                    leftChildID = innerNodeID;
                } else if (tree.getRightChildOfNode(nodeIndex) == innerNode) {
                    rightChildID = innerNodeID;
                }
            }

            nodeDataMap->insert(
                std::pair<node_index_t, std::pair<std::string, std::string>>(
                    nodeID,
                    std::pair<std::string, std::string>(
                        nodeDataToJson(tree, nodeIndex, leftChildID,
                                       rightChildID, scalers),
                        nodeClassCountsToJson(tree, nodeIndex, nClasses))));
        }

        return *nodeDataMap;
    }

    template <class T>
    static std::string
    nodeClassCountsToJson(T &tree, typename T::node_index_t nodeIndex,
                          typename T::class_index_t nClasses) {
        typedef typename T::class_index_t class_index_t;

        std::string array[nClasses];

        for (class_index_t i = 0; i < nClasses; i++) {
            array[i] =
                std::to_string(
                    tree.getNode(nodeIndex).getData().getSampleCountPerClass(
                        i)) +
                ".0";
        }

        const std::string intermediateArray[1] = {arrayToJson(array, nClasses)};
        return arrayToJson(intermediateArray, 1);
    }

    template <class T>
    static std::string
    nodeDataToJson(T tree, typename T::node_index_t nodeIndex,
                   typename T::node_index_t leftChildID,
                   typename T::node_index_t rightChildID,
                   const typename T::_DataClass::sampleScaler
                       scalers[T::_DataClass::N_Attributes] = NULL) {

        const std::string array[7] = {
            tree.hasLeftChild(nodeIndex) ? std::to_string(leftChildID) : "-1",
            tree.hasRightChild(nodeIndex) ? std::to_string(rightChildID) : "-1",
            tree.isNodeSplit(nodeIndex)
                ? std::to_string(tree.getNodeSplitAttributeIndex(nodeIndex))
                : "-2",
            tree.isNodeSplit(nodeIndex)
                ? std::to_string(tcm::makePrimitive(
                      scalers != NULL
                          ? scalers[tree.getNodeSplitAttributeIndex(nodeIndex)](
                                tree.getNodeSplitValue(nodeIndex))
                          : tree.getNodeSplitValue(nodeIndex)))
                : "-2.0",
            std::to_string(tcm::makePrimitive(
                tree.getNode(nodeIndex).getData().getImpurity())),
            std::to_string(
                tree.getNode(nodeIndex).getData().getSampleCountTotal()),
            std::to_string(
                tree.getNode(nodeIndex).getData().getSampleCountTotal()) +
                ".0"};

        return arrayToJson(array, 7);
    }

    template <class T, class fn_T>
    static void DFS(T &tree, typename T::node_index_t nodeIndex,
                    fn_T function) {
        typename T::node_index_t c = 0;
        _DFS_handle(tree, nodeIndex, function, c);
    }

    template <class T>
    static void copyNode(T &oldTree, T &newTree,
                         typename T::node_index_t oldNodeIndex,
                         typename T::node_index_t newNodeIndex) {

        if (oldTree.isNodeSplit(oldNodeIndex)) {
            newTree.splitNode(newNodeIndex,
                              oldTree.getNodeSplitAttributeIndex(oldNodeIndex),
                              oldTree.getNodeSplitValue(oldNodeIndex));
        }

        if (oldTree.hasLeftChild(oldNodeIndex)) {
            copyNode(oldTree, newTree, oldTree.getLeftChildOfNode(oldNodeIndex),
                     newTree.getLeftChildOfNode(newNodeIndex));
        }
        if (oldTree.hasRightChild(oldNodeIndex)) {
            copyNode(oldTree, newTree,
                     oldTree.getRightChildOfNode(oldNodeIndex),
                     newTree.getRightChildOfNode(newNodeIndex));
        }
    }

    template <class T>
    static void
    inferDataset(T &tree,
                 typename T::data_t
                     dataset[][T::_NodeClass::_DataClass::N_Attributes + 1],
                 typename T::sample_count_t datasetSize) {
        for (typename T::sample_count_t i = 0; i < datasetSize; i++) {
            typename T::node_index_t nodeIndex = tree.getRootNodeIndex();

            do {
                nodeIndex = tree.evaluateNodeSplit(nodeIndex, dataset[i]);
                tree.getNode(nodeIndex).getData().update(
                    dataset[i],
                    dataset[i][T::_NodeClass::_DataClass::N_Attributes]);

            } while (nodeIndex != 0);
        }
    }

    template <class T>
    static void
    inferDataset(T &tree,
                 typename T::data_t dataset[][T::_DataClass::N_Attributes],
                 typename T::class_index_t classif[],
                 typename T::sample_count_t datasetSize) {
        for (typename T::sample_count_t i = 0; i < datasetSize; i++) {
            typename T::node_index_t nodeIndex = tree.getRootNodeIndex();

            do {
                nodeIndex = tree.evaluateNodeSplit(nodeIndex, dataset[i]);
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
    static void _DFS_handle(T &tree, typename T::node_index_t nodeIndex,
                            fn_T function,
                            typename T::node_index_t &nodeCounter) {

        function(nodeIndex, nodeCounter++);

        if (tree.hasLeftChild(nodeIndex)) {
            _DFS_handle(tree, tree.getLeftChildOfNode(nodeIndex), function,
                        nodeCounter);
        }
        if (tree.hasRightChild(nodeIndex)) {
            _DFS_handle(tree, tree.getRightChildOfNode(nodeIndex), function,
                        nodeCounter);
        }
    }
};

#endif
