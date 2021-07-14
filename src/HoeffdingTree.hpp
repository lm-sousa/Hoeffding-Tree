#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include <cmath>
#include <iostream>
#include <tuple>

#include "BinaryTree.hpp"
#include "Node.hpp"

template <class Node = Node<>, uint capacity = 100>
class HoeffdingTree : public BinaryTree<Node, capacity> {
  public:
    typedef Node _NodeClass;
    typedef typename _NodeClass::_DataClass _DataClass;
    typedef _DataClass Data;
    typedef typename _NodeClass::node_index_t node_index_t;
    typedef typename _DataClass::data_t data_t;
    typedef typename _DataClass::attribute_index_t attribute_index_t;
    typedef typename _DataClass::class_index_t class_index_t;
    typedef typename _DataClass::quantile_index_t quantile_index_t;
    typedef typename _DataClass::point_index_t point_index_t;
    typedef typename _DataClass::sample_count_t sample_count_t;

    /**
     * @brief Construct a new Hoeffding Tree< Data> object
     *
     * @param r Range of variables
     * @param sigma acceptable error margin (0.0 to 1.0)
     */
    HoeffdingTree(data_t r, data_t sigma, data_t tau)
        : _hoeffdingBoundConstant(r * (tcm::sqrt(-tcm::log(sigma) / 2))), r(r),
          sigma(sigma), tau(tau) {}

    data_t getR() { return r; }

    data_t getSigma() { return sigma; }

    data_t getTau() { return tau; }

    std::pair<class_index_t, data_t>
    train(data_t sample[_DataClass::N_Attributes], class_index_t classif,
          bool doSplitTrial) {

        node_index_t nodeIndex = this->sortSample(sample);
        _NodeClass &node = this->getNode(nodeIndex);
        Data &nodeData = node.getData();

        nodeData.update(sample, classif);

        if (doSplitTrial) {
            attribute_index_t attributeIndex;
            data_t splitValue;
            data_t G;

            std::tie(attributeIndex, splitValue, G) = nodeData.evaluateSplit();

            data_t hBound = hoeffdingBound(nodeData.getSampleCountTotal());

            if (G > hBound || tau > hBound) {
                this->splitNode(node, attributeIndex, splitValue);
                /*std::cout << "split! --> " << attributeIndex << " : "
                          << splitValue << std::endl;*/
            }
        }

        return node.infer();
    }

    std::pair<class_index_t, data_t> infer(data_t sample[]) {
        node_index_t nodeIndex = this->sortSample(sample);
        _NodeClass &node = this->getNode(nodeIndex);

        return node.infer();
    }

    /**
     * @brief Calculates the Hoeffding Bound
     *
     * @param n Number of samples in the leaf node
     * @return constexpr float Hoeffding bound
     */
    constexpr data_t hoeffdingBound(sample_count_t n) {
        return _hoeffdingBoundConstant / tcm::sqrt((data_t)n);
    }

  protected:
    const data_t _hoeffdingBoundConstant = 0;
    const data_t r;
    const data_t sigma;
    const data_t tau;

    const data_t _errorMargin = 0;
};

#endif
