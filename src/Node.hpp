#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <stdlib.h>

#include "NodeData.hpp"

template <class Data = NodeData<>> class Node {

  public:
    typedef Data _DataClass;

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

    bool hasChildren() { return hasLeftChild() || hasRightChild(); }

    /**
     * @brief Infer the node
     *
     * @return Node*
     */
    Node *infer(typename Data::datatype x[]) {

        if (!hasChildren()) {
            return NULL;
        }

        if (_checkSplit(x)) {
            return getLeftChild();
        } else {
            return getRightChild();
        }
    }

  private:
    Data _data;
    Node *_parent = NULL;
    Node *_leftChild = NULL;
    Node *_rightChild = NULL;

    void _setParent(Node *parent) { _parent = parent; }

    /**
     * @brief Index of the Attribute where the split is calculated
     *  '0' if no slit on this node.
     *
     */
    uint _splitAttributeIndex = 0;

    typename Data::datatype _splitValue = 0;

    bool _checkSplit(typename Data::datatype x[]) {
        return x[_splitAttributeIndex - 1] <= _splitValue;
    }
};

#endif
