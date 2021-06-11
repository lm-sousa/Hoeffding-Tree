#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include <bits/stdint-uintn.h>
#include <iostream>
#include <math.h>
#include <tuple>

#include "BinaryTree.hpp"
#include "Node.hpp"

template <class Data> class HoeffdingTree : public BinaryTree<Node<Data>> {
  public:
    typedef Data _DataClass;
    typedef typename Data::datatype datatype;

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

    void train(datatype sample[], uint classif, bool doSplitTrial) {

        Node<Data> *node = this->sortSample(sample);
        Data &nodeData = node->getData();

        nodeData.update(sample, classif);

        if (doSplitTrial) {
            uint attributeIndex;
            datatype splitValue;
            datatype G;

            std::tie(attributeIndex, splitValue, G) = nodeData.evaluateSplit();

            datatype hBound = hoeffdingBound(nodeData.getSampleCountTotal());

            if (G > hBound || tau > hBound) {
                node->setSplit(attributeIndex, splitValue);
                this->addLeftChild(node);
                this->addRightChild(node);
                std::cout << "split! --> " << attributeIndex << " : "
                          << splitValue << std::endl;
            }
        }
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
