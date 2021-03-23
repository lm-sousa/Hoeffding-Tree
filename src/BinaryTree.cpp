#include "BinaryTree.hpp"

BinaryTree::BinaryTree() {

    for (auto node : this->_nodes) {
        node._clearNode();
        node._setTree(this);
    }

    Node *rootNode = this->getRootNode();
    rootNode->setUsed();
}

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

uint BinaryTree::getCurrentSize() {
    uint cnt = 0;
    for (auto node : this->_nodes) {
        cnt += node.isInUse();
    }
    return cnt;
}

uint BinaryTree::getCapacity() { return this->_capacity; }

BinaryTree::Node *BinaryTree::getRootNode() { return &(this->_nodes[0]); }

BinaryTree::Node *BinaryTree::_getNextFreeNode() {
    for (uint i = 0; i < MAX_TREE_SIZE; i++) {
        if (!_nodes[i].isInUse())
            return &(_nodes[i]);
    }

    return NULL;
}