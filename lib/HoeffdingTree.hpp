#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include <bits/stdint-uintn.h>
#include <iostream>
#include <math.h>
#include <tuple>

#include "BinaryTree.hpp"
#include "Node.hpp"

template <class Node = Node<>, uint8_t capacity = 100>
class HoeffdingTree : public BinaryTree<Node, capacity> {
  public:
    typedef Node _NodeClass;
    typedef typename _NodeClass::node_index_t node_index_t;
    typedef typename _NodeClass::_DataClass _DataClass;
    typedef typename _DataClass::datatype datatype;
    typedef _DataClass Data;

    /**
     * @brief Construct a new Hoeffding Tree< Data> object
     *
     * @param r Range of variables
     * @param sigma acceptable error margin (0.0 to 1.0)
     */
    HoeffdingTree(datatype r, datatype sigma, datatype tau)
        : _hoeffdingBoundConstant(r * (sqrt(-log(sigma) / 2))), r(r),
          sigma(sigma), tau(tau) {}

    datatype getR() { return r; }

    datatype getSigma() { return sigma; }

    datatype getTau() { return tau; }

    std::pair<uint, datatype> train(datatype sample[_DataClass::N_Attributes],
                                    uint classif, bool doSplitTrial) {

        node_index_t nodeIndex = this->sortSample(sample);
        _NodeClass &node = this->getNode(nodeIndex);
        Data &nodeData = node.getData();

        nodeData.update(sample, classif);

        if (doSplitTrial) {
            uint attributeIndex;
            datatype splitValue;
            datatype G;

            std::tie(attributeIndex, splitValue, G) = nodeData.evaluateSplit();

            datatype hBound = hoeffdingBound(nodeData.getSampleCountTotal());

            if (G > hBound || tau > hBound) {
                this->splitNode(node, attributeIndex, splitValue);
                /*std::cout << "split! --> " << attributeIndex << " : "
                          << splitValue << std::endl;*/
            }
        }

        return node.infer();
    }

    std::pair<uint, datatype> infer(datatype sample[]) {
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
    constexpr datatype hoeffdingBound(uint n) {
        return _hoeffdingBoundConstant / sqrt(n);
    }

  protected:
    const datatype _hoeffdingBoundConstant = 0;
    const datatype r;
    const datatype sigma;
    const datatype tau;

    const datatype _errorMargin = 0;
    uint splitAttribute = 0;
    uint splitValue = 0; // <=
};

#endif
