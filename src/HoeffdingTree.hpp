#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include <bits/stdint-uintn.h>
#include <math.h>

#include "BinaryTree.hpp"
#include "Node.hpp"

template <class Data> class HoeffdingTree : public BinaryTree<Node<Data>> {
  public:
    /**
     * @brief Construct a new Hoeffding Tree< Data> object
     *
     * @param r Range of variables
     * @param sigma acceptable error margin (0.0 to 1.0)
     */
    HoeffdingTree(typename Data::datatype r, typename Data::datatype sigma)
        : _hoeffdingBoundConstant(r * (sqrt(-log(sigma) / 2))) {}

    void train(typename Data::datatype sample[], uint classif,
               bool doSplitTrial) {

        this->sortSample(sample)->getData().update(sample, classif);

        if (doSplitTrial) {
            // TODO Algo3: lines 13+
        }
    }

    /**
     * @brief Calculates the Hoeffding Bound
     *
     * @param n Number of samples in the leaf node
     * @return constexpr float Hoeffding bound
     */
    constexpr typename Data::datatype hoeffdingBound(uint n) {
        return _hoeffdingBoundConstant / sqrt(n);
    }

  protected:
    const typename Data::datatype _hoeffdingBoundConstant = 0;

    const typename Data::datatype _errorMargin = 0;
    uint splitAttribute = 0;
    uint splitValue = 0; // <=
};

#endif
