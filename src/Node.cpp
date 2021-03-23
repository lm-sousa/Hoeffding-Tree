#include "BinaryTree.hpp"

bool BinaryTree::Node::isInUse() { return this->isUsed; }

void BinaryTree::Node::_setUsedStatus(bool isInUse) { this->isUsed = isInUse; }

void BinaryTree::Node::setUsed() { this->_setUsedStatus(true); }

void BinaryTree::Node::setUnused() { this->_setUsedStatus(false); }

void *BinaryTree::Node::getData() { return this->data; }

void BinaryTree::Node::setData(void *data) { this->data = data; }

void BinaryTree::Node::clearData() { this->setData(NULL); }

bool BinaryTree::Node::hasParent() { return this->getParent(); }

BinaryTree::Node *BinaryTree::Node::getParent() { return this->_parent; }

bool BinaryTree::Node::hasLeftChild() { return this->getLeftChild(); }

BinaryTree::Node *BinaryTree::Node::getLeftChild() { return this->_leftChild; }

bool BinaryTree::Node::hasRightChild() { return this->getRightChild(); }

BinaryTree::Node *BinaryTree::Node::getRightChild() {
    return this->_rightChild;
}

void BinaryTree::Node::_setParent(Node *parent) { this->_parent = parent; }

void BinaryTree::Node::_setLeftChild(Node *child) {
    this->_leftChild = child;
    if (child) {
        child->_setParent(this);
    }
}

void BinaryTree::Node::_setRightChild(Node *child) {
    this->_rightChild = child;
    if (child) {
        child->_setParent(this);
    }
}

void BinaryTree::Node::_setTree(BinaryTree *tree) { this->tree = tree; }

void BinaryTree::Node::_clearParent() { this->_setParent(NULL); }

void BinaryTree::Node::_clearLeftChild() { this->_setLeftChild(NULL); }

void BinaryTree::Node::_clearRightChild() { this->_setRightChild(NULL); }

void BinaryTree::Node::_clearNode() {
    this->setUnused();
    this->clearData();
    this->_clearParent();
    this->_clearLeftChild();
    this->_clearRightChild();
}

BinaryTree::Node &BinaryTree::Node::addLeftChild() {}

BinaryTree::Node &BinaryTree::Node::addRightChild() {}

void BinaryTree::Node::deleteNode() {
    if (this->hasParent()) {
        BinaryTree::Node *parent = this->getParent();
        if (parent->hasLeftChild() && this == parent->getLeftChild()) {
            parent->_clearLeftChild();
        }
        if (parent->hasRightChild() && this == parent->getRightChild()) {
            parent->_clearRightChild();
        }
    }
    BinaryTree::DFS(this, &BinaryTree::Node::_clearNode);
    this->_clearNode();
}

void BinaryTree::Node::deleteLeftChild() {
    if (this->hasLeftChild()) {
        this->getLeftChild()->deleteNode();
    }
}

void BinaryTree::Node::deleteRightChild() {
    if (this->hasRightChild()) {
        this->getRightChild()->deleteNode();
    }
}
