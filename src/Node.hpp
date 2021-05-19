#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <stdlib.h>

#include "NodeData.hpp"

template <class Data = NodeData> class Node {

  public:
    void *getData() { return _data; }
    void setData(void *data) { _data = data; }
    void clearData() { setData(NULL); }

    bool hasParent() { return getParent(); }
    Node *getParent() { return _parent; }

    bool hasLeftChild() { return getLeftChild(); }
    Node *getLeftChild() { return _leftChild; }
    void setLeftChild(Node *child) {
        _leftChild = child;
        child->_setParent(this);
    }

    bool hasRightChild() { return getRightChild(); }
    Node *getRightChild() { return _rightChild; }
    void setRightChild(Node *child) {
        _rightChild = child;
        child->_setParent(this);
    }

  private:
    Data _data;
    Node *_parent = NULL;
    Node *_leftChild = NULL;
    Node *_rightChild = NULL;

    void _setParent(Node *parent) { _parent = parent; }
};

#endif
