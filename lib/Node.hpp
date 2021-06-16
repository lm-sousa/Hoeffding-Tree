#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <stdlib.h>
#include <utility>

#include "NodeData.hpp"

template <class Data = NodeData<>, typename node_index_T = int8_t> class Node {

  public:
    typedef Data _DataClass;
    typedef typename Data::datatype datatype;
    typedef node_index_T node_index_t;

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
    // bool hasParent() { return getParent(); }

    /**
     * @brief Get the parent Node object
     *
     * @return Node* Pointer to the parent Node object
     */
    // Node *getParent() { return _parent; }

    /**
     * @brief Check if Node has a left child
     *
     * @return true
     * @return false
     */
    bool hasLeftChild() { return getLeftChild() >= 0; }

    /**
     * @brief Get the left child Node object
     *
     * @return Node* Pointer to the left child Node object
     */
    node_index_t getLeftChild() { return _leftChild; }

    /**
     * @brief Set the left child Node object
     *
     * @param child Pointer to the left child Node object
     */
    void setLeftChild(node_index_t child) {
        _leftChild = child;
        // child->_setParent(this);
    }

    /**
     * @brief Check if Node has a right child
     *
     * @return true
     * @return false
     */
    bool hasRightChild() { return getRightChild() >= 0; }

    /**
     * @brief Get the right child Node object
     *
     * @return Node* Pointer to the right child Node object
     */
    node_index_t getRightChild() { return _rightChild; }

    /**
     * @brief Set the right child Node object
     *
     * @param child Pointer to the right child Node object
     */
    void setRightChild(node_index_t child) {
        _rightChild = child;
        // child->_setParent(this);
    }

    /**
     * @brief Check if the Node has any children
     *
     * @return true
     * @return false
     */
    bool hasChildren() { return hasLeftChild() || hasRightChild(); }

    bool isSplit() { return hasChildren(); }

    /**
     * @brief Sort the sample through the Node
     *
     * @return Node*
     */
    node_index_t sortSample(datatype x[]) {

        if (!isSplit()) {
            return -1;
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

    uint getSplitAttributeIndex() { return _splitAttributeIndex; }

    datatype getSplitValue() { return _splitValue; }

    std::pair<uint, datatype> infer() {
        return std::make_pair(getData().getMostCommonClass(),
                              getData().getConfidence());
    }

  private:
    Data _data;
    // node_index _parent = -1;
    node_index_t _leftChild = -1;
    node_index_t _rightChild = -1;

    // void _setParent(Node *parent) { _parent = parent; }

    /**
     * @brief Index of the Attribute where the split is calculated
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
        return x[getSplitAttributeIndex()] <= getSplitValue();
    }
};

#endif
