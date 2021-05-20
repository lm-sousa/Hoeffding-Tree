#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include <bits/stdint-uintn.h>
#include <math.h>

#include "BinaryTree.hpp"
#include "Node.hpp"

template <class Data> class HoeffdingTree : public BinaryTree<Node<Data>> {
  public:
    /**
     * @brief Creates a HoeffdingTree object
     *
     * @param r Range of variables
     * @param sigma acceptable error margin (0.0 to 1.0)
     */
    HoeffdingTree<Data>(uint r, float sigma)
        : _hoeffdingBoundConstant(r * (sqrt(-log(sigma) / 2))) {}

    void infer(typename Data::datatype data[]);
    void train(typename Data::datatype data[]);

    /**
     * @brief Asymmetric signum function
     *
     * @param z
     * @param alpha
     * @return constexpr uint
     */
    constexpr uint sgnAlpha(typename Data::datatype z, float alpha) {
        return z < 0 ? -alpha : 1 - alpha;
    }

    /**
     * @brief Calculates the Hoeffding Bound
     *
     * @param r Range of variable
     * @param sigma acceptable error margin (0.0 to 1.0)
     * @param n Number of samples in the leaf node
     * @return float Hoeffding bound
     */
    float _hoeffdingBound(uint n) { return _hoeffdingBoundConstant / sqrt(n); }

  protected:
    const float _hoeffdingBoundConstant = 0;

    const float _errorMargin = 0;
    uint splitAttribute = 0;
    uint splitValue = 0; // <
};

#endif
