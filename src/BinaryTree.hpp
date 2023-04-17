#ifndef __BINARY_TREE_HPP__
#define __BINARY_TREE_HPP__

#include <cstddef>
#include <functional>
#include <stdlib.h>

#include "TypeChooser.hpp"

template <class Node_T, uintmax_t capacity_T = 100> class BinaryTree {

  public:
    typedef Node_T _NodeClass;
    typedef typename _NodeClass::_DataClass _DataClass;
    typedef typename _DataClass::data_t data_t;
    typedef typename _DataClass::attribute_index_t attribute_index_t;
    typedef typename _DataClass::class_index_t class_index_t;
    typedef typename _DataClass::quantile_index_t quantile_index_t;
    typedef typename _DataClass::point_index_t point_index_t;
    typedef typename _DataClass::sample_count_t sample_count_t;
    typedef TCU<capacity_T> node_index_t;

    static node_index_t getCapacity() { return capacity_T; }
    node_index_t getSize() { return _size; }

    _NodeClass &getNode(node_index_t index) { return _nodes[index]; }

    _NodeClass &getRootNode() { return getNode(getRootNodeIndex()); }

    node_index_t getRootNodeIndex() { return 0; }

    /**
     * @brief Sort the sample through the tree
     *
     * @param x Data point - Array of attributes
     * @return leaf node index where the sample is sorted
     */
    node_index_t sortSample(data_t x[]) {
        node_index_t newNode = getRootNodeIndex(), node;

    BinaryTree_sortSample__nodes:
        do {
#pragma HLS LOOP_TRIPCOUNT min = 1 max = capacity
            node = newNode;
            newNode = evaluateNodeSplit(node, x);
        } while (newNode != 0);

        return node;
    }

    void splitNode(node_index_t nodeIndex, attribute_index_t attributeIndex,
                   data_t splitValue) {

        _treeInformation[nodeIndex].splitAttributeIndex = attributeIndex;
        _treeInformation[nodeIndex].splitValue = splitValue;
        _treeInformation[nodeIndex].leftChild = _reserveNextFreeNode();
        _treeInformation[nodeIndex].rightChild = _reserveNextFreeNode();
    }

    node_index_t evaluateNodeSplit(node_index_t nodeIndex, data_t x[]) {
        return x[_treeInformation[nodeIndex].splitAttributeIndex] <=
                       _treeInformation[nodeIndex].splitValue
                   ? _treeInformation[nodeIndex].leftChild
                   : _treeInformation[nodeIndex].rightChild;
    }

    /**
     * @brief Check if Node has a left child
     *
     * @return true
     * @return false
     */
    bool hasLeftChild(node_index_t nodeIndex) {
        return getLeftChildOfNode(nodeIndex) > 0;
    }

    /**
     * @brief Get the left child Node object
     *
     * @return Node* Pointer to the left child Node object
     */
    node_index_t getLeftChildOfNode(node_index_t nodeIndex) {
        return _treeInformation[nodeIndex].leftChild;
    }

    /**
     * @brief Check if Node has a right child
     *
     * @return true
     * @return false
     */
    bool hasRightChild(node_index_t nodeIndex) {
        return getRightChildOfNode(nodeIndex) > 0;
    }

    /**
     * @brief Get the right child Node object
     *
     * @return Node* Pointer to the right child Node object
     */
    node_index_t getRightChildOfNode(node_index_t nodeIndex) {
        return _treeInformation[nodeIndex].rightChild;
    }

    bool isNodeSplit(node_index_t nodeIndex) {
        return _treeInformation[nodeIndex].leftChild ||
               _treeInformation[nodeIndex].rightChild;
    }

    attribute_index_t getNodeSplitAttributeIndex(node_index_t nodeIndex) {
        return _treeInformation[nodeIndex].splitAttributeIndex;
    }

    data_t getNodeSplitValue(node_index_t nodeIndex) {
        return _treeInformation[nodeIndex].splitValue;
    }

  private:
    node_index_t _size = 1;
    struct _NodeInfo {
        node_index_t leftChild = 0;
        node_index_t rightChild = 0;

        /**
         * @brief Index of the Attribute where the split is calculated
         *
         */
        attribute_index_t splitAttributeIndex = 0;

        /**
         * @brief Value where the split has occured.
         *
         */
        data_t splitValue = 0;
    };

    _NodeInfo _treeInformation[capacity_T];
    _NodeClass _nodes[capacity_T];

    node_index_t _reserveNextFreeNode() {
        return (_size >= capacity_T) ? static_cast<node_index_t>(0) : _size++;
    }
};

#endif
