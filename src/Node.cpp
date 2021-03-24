#include "BinaryTree.hpp"

void BinaryTree::Node::setTree(BinaryTree *tree) { _tree = tree; }

void *BinaryTree::Node::getData() { return _data; }

void BinaryTree::Node::setData(void *data) { _data = data; }

void BinaryTree::Node::clearData() { setData(NULL); }

bool BinaryTree::Node::hasParent() { return getParent(); }

BinaryTree::Node *BinaryTree::Node::getParent() { return _parent; }

bool BinaryTree::Node::hasLeftChild() { return getLeftChild(); }

BinaryTree::Node *BinaryTree::Node::getLeftChild() { return _leftChild; }

BinaryTree::Node *BinaryTree::Node::addLeftChild() {
    Node *newNode = _tree->_getNextFreeNode();
    if (!newNode) {
        return NULL;
    }

    _setLeftChild(newNode);
    _tree->increaseSize();

    return newNode;
}

bool BinaryTree::Node::hasRightChild() { return getRightChild(); }

BinaryTree::Node *BinaryTree::Node::getRightChild() { return _rightChild; }

BinaryTree::Node *BinaryTree::Node::addRightChild() {
    Node *newNode = _tree->_getNextFreeNode();
    if (!newNode) {
        return NULL;
    }

    _setRightChild(newNode);
    _tree->increaseSize();

    return newNode;
}

void BinaryTree::Node::_setParent(Node *parent) { _parent = parent; }

void BinaryTree::Node::_setLeftChild(Node *child) {
    _leftChild = child;
    child->_setParent(this);
}

void BinaryTree::Node::_setRightChild(Node *child) {
    _rightChild = child;
    child->_setParent(this);
}
