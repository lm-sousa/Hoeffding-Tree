#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <stdlib.h>

#include "NodeData.hpp"

template <class Data = NodeData<>> class Node {

  public:
    typedef Data _DataClass;
    typedef typename Data::datatype datatype;

    /**
     * @brief Get the Data object
     *
     * @return void* Pointer to the Data object
     */
    Data &getData() { return _data; }

    /**
     * @brief Check if Node has a parent
     *
     * @return true
     * @return false
     */
    bool hasParent() { return getParent(); }

    /**
     * @brief Get the parent Node object
     *
     * @return Node* Pointer to the parent Node object
     */
    Node *getParent() { return _parent; }

    /**
     * @brief Check if Node has a left child
     *
     * @return true
     * @return false
     */
    bool hasLeftChild() { return getLeftChild(); }

    /**
     * @brief Get the left child Node object
     *
     * @return Node* Pointer to the left child Node object
     */
    Node *getLeftChild() { return _leftChild; }

    /**
     * @brief Set the left child Node object
     *
     * @param child Pointer to the left child Node object
     */
    void setLeftChild(Node *child) {
        _leftChild = child;
        child->_setParent(this);
    }

    /**
     * @brief Check if Node has a right child
     *
     * @return true
     * @return false
     */
    bool hasRightChild() { return getRightChild(); }

    /**
     * @brief Get the right child Node object
     *
     * @return Node* Pointer to the right child Node object
     */
    Node *getRightChild() { return _rightChild; }

    /**
     * @brief Set the right child Node object
     *
     * @param child Pointer to the right child Node object
     */
    void setRightChild(Node *child) {
        _rightChild = child;
        child->_setParent(this);
    }

    /**
     * @brief Check if the Node has any children
     *
     * @return true
     * @return false
     */
    bool hasChildren() { return hasLeftChild() || hasRightChild(); }

    /**
     * @brief Sort the sample through the Node
     *
     * @return Node*
     */
    Node *sortSample(datatype x[]) {

        if (!hasChildren()) {
            return NULL;
        }

        if (_checkSplit(x)) {
            return getLeftChild();
        } else {
            return getRightChild();
        }
    }

    void setSplit(uint attributeIndex, datatype splitValue) {
        _splitAttributeIndex = attributeIndex;
        _splitValue = splitValue;
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

    /**
     * @brief Value where the split has occured.
     *
     */
    datatype _splitValue = 0;

    /**
     * @brief Check data point against the defined split point
     *
     * @param x Data point - Array of attributes
     * @return true Value is less than or equal to the split point
     * @return false Value is greater than the split point
     */
    bool _checkSplit(datatype x[]) {
        return x[_splitAttributeIndex - 1] <= _splitValue;
    }
};

#endif
