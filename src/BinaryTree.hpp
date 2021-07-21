#ifndef __BINARY_TREE_HPP__
#define __BINARY_TREE_HPP__

#include <cstddef>
#include <functional>
#include <stdlib.h>

template <class Node, uint capacity = 100> class BinaryTree {

  public:
    typedef Node _NodeClass;
    typedef typename _NodeClass::_DataClass _DataClass;
    typedef typename _NodeClass::node_index_t node_index_t;
    typedef typename _DataClass::data_t data_t;
    typedef typename _DataClass::attribute_index_t attribute_index_t;
    typedef typename _DataClass::class_index_t class_index_t;
    typedef typename _DataClass::quantile_index_t quantile_index_t;
    typedef typename _DataClass::point_index_t point_index_t;
    typedef typename _DataClass::sample_count_t sample_count_t;

    constexpr node_index_t getCapacity() { return capacity; }
    node_index_t getSize() { return _size; }
    void increaseSize() { _size++; }
    bool canAddNode() { return _size < capacity; }

    Node &getNode(node_index_t index) { return _nodes[index]; }

    Node &getRootNode() { return getNode(getRootNodeIndex()); }

    node_index_t getRootNodeIndex() { return 0; }

    node_index_t addLeftChild(Node &node) {

        node_index_t newNodeIndex = _getNextFreeNode();
        if (newNodeIndex == 0) {
            return 0;
        }

        node.setLeftChild(newNodeIndex);
        this->increaseSize();

        return newNodeIndex;
    }

    node_index_t addRightChild(Node &node) {
        node_index_t newNodeIndex = _getNextFreeNode();
        if (newNodeIndex == 0) {
            return 0;
        }

        node.setRightChild(newNodeIndex);
        this->increaseSize();

        return newNodeIndex;
    }

    node_index_t sortSample(data_t x[]) {
        node_index_t newNode = getRootNodeIndex(), node;

    BinaryTree_sortSample__nodes:
        do {
#pragma HLS LOOP_TRIPCOUNT min = 1 max = capacity
            node = newNode;
            newNode = getNode(node).sortSample(x);
        } while (newNode != 0);

        return node;
    }

    void splitNode(Node &node, attribute_index_t attributeIndex,
                   data_t splitValue) {
        node.setSplit(attributeIndex, splitValue);
        this->addLeftChild(node);
        this->addRightChild(node);
    }

  private:
    node_index_t _size = 1;
    Node _nodes[capacity];

    node_index_t _getNextFreeNode() {
        if (getSize() >= getCapacity()) {
            return 0;
        } else {
            return getSize();
        }
    }
};

#endif
