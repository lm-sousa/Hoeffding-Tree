#ifndef __BINARY_TREE_HPP__
#define __BINARY_TREE_HPP__

#include <bits/stdint-uintn.h>
#include <cstddef>
#include <functional>
#include <stdlib.h>

template <class Node, uint8_t capacity = 100> class BinaryTree {

  public:
    typedef Node _NodeClass;
    typedef typename _NodeClass::_DataClass _DataClass;
    typedef typename _NodeClass::node_index_t node_index_t;
    typedef typename _DataClass::data_t data_t;

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

        do {
            node = newNode;
            newNode = getNode(node).sortSample(x);
        } while (newNode != 0);

        return node;
    }

    void splitNode(Node &node, uint attributeIndex, data_t splitValue) {
        node.setSplit(attributeIndex, splitValue);
        this->addLeftChild(node);
        this->addRightChild(node);
    }

  private:
    uint8_t _size = 1;
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
