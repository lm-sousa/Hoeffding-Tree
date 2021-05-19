#ifndef __BINARY_TREE_HPP__
#define __BINARY_TREE_HPP__

#include <bits/stdint-uintn.h>
#include <cstddef>
#include <functional>
#include <stdlib.h>

#include "Node.hpp"

template <class Node, uint8_t capacity = 100> class BinaryTree {

  public:
    uint8_t getCapacity() { return _capacity; }
    uint8_t getSize() { return _size; }
    void increaseSize() { _size++; }
    bool canAddNode() { return _size < _capacity; }

    Node *getRootNode() { return &_nodes[0]; }

    Node *addLeftChild(Node *node) {

        Node *newNode = _getNextFreeNode();
        if (!newNode) {
            return NULL;
        }

        node->setLeftChild(newNode);
        this->increaseSize();

        return newNode;
    }

    Node *addRightChild(Node *node) {
        Node *newNode = _getNextFreeNode();
        if (!newNode) {
            return NULL;
        }

        node->setRightChild(newNode);
        this->increaseSize();

        return newNode;
    }

    /*static void DFS(Node *origin, void (BinaryTree::Node::*function)()) {
        BinaryTree::Node *_node = origin;
        BinaryTree::Node *_parent = origin;
        do {
            while (_node->hasLeftChild()) {
                _parent = _node;
                _node = _node->getLeftChild();
            }
            while (_node->hasRightChild()) {
                _parent = _node;
                _node = _node->getRightChild();
            }
            (_node->*function)();
            _node = _parent;
            _parent = _node->getParent();
        } while (_node != origin || _node->hasRightChild());
    }*/

  private:
    const uint8_t _capacity = capacity;
    uint8_t _size = 1;
    Node _nodes[capacity];

    Node *_getNextFreeNode() { return &_nodes[getSize()]; }
};

#endif