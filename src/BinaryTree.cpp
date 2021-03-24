#include "BinaryTree.hpp"
#include <iostream>
#include <ostream>

/*BinaryTree::BinaryTree() {
    for (auto node : _nodes) {
        node.setTree(this);
    }
}*/

void BinaryTree::prime() {
    for (auto node : _nodes) {
        node.setTree(this);
    }
}

uint BinaryTree::getCapacity() { return _capacity; }

uint BinaryTree::getSize() { return _size; }

void BinaryTree::increaseSize() { _size++; }

bool BinaryTree::canAddNode() { return _size < _capacity; }

BinaryTree::Node *BinaryTree::getRootNode() { return &_nodes[0]; }

BinaryTree::Node *BinaryTree::_getNextFreeNode() { return &_nodes[getSize()]; }

/*
void BinaryTree::DFS(Node *origin, void (BinaryTree::Node::*function)()) {
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
}
*/