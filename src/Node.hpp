#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <stdlib.h>
#include <utility>

#include "NodeData.hpp"

template <class Data = NodeData<>,
          typename node_index_T = TypeChooser_Unsigned(100)>
class Node {

  public:
    typedef node_index_T node_index_t;
    typedef Data _DataClass;
    typedef typename Data::data_t data_t;
    typedef typename Data::attribute_index_t attribute_index_t;
    typedef typename Data::class_index_t class_index_t;
    typedef typename Data::quantile_index_t quantile_index_t;
    typedef typename Data::point_index_t point_index_t;

    /**
     * @brief Get the Data object
     *
     * @return void* Pointer to the Data object
     */
    Data &getData() { return _data; }

    /**
     * @brief Check if Node has a left child
     *
     * @return true
     * @return false
     */
    bool hasLeftChild() { return getLeftChild() > 0; }

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
    bool hasRightChild() { return getRightChild() > 0; }

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
    node_index_t sortSample(data_t x[]) {

        if (!isSplit()) {
            return 0;
        }

        if (_checkSplit(x)) {
            return getLeftChild();
        } else {
            return getRightChild();
        }
    }

    void setSplit(attribute_index_t attributeIndex, data_t splitValue) {
        _splitAttributeIndex = attributeIndex;
        _splitValue = splitValue;
    }

    attribute_index_t getSplitAttributeIndex() { return _splitAttributeIndex; }

    data_t getSplitValue() { return _splitValue; }

    std::pair<class_index_t, data_t> infer() {
        return std::make_pair(getData().getMostCommonClass(),
                              getData().getConfidence());
    }

  private:
    Data _data;
    node_index_t _leftChild = 0;
    node_index_t _rightChild = 0;

    // void _setParent(Node *parent) { _parent = parent; }

    /**
     * @brief Index of the Attribute where the split is calculated
     *
     */
    attribute_index_t _splitAttributeIndex = 0;

    /**
     * @brief Value where the split has occured.
     *
     */
    data_t _splitValue = 0;

    /**
     * @brief Check data point against the defined split point
     *
     * @param x Data point - Array of attributes
     * @return true Value is less than or equal to the split point
     * @return false Value is greater than the split point
     */
    bool _checkSplit(data_t x[]) {
        return x[getSplitAttributeIndex()] <= getSplitValue();
    }
};

#endif
