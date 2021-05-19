#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include "BinaryTree.hpp"
#include <bits/stdint-uintn.h>

#include "Node.hpp"

template <class Data> class HoeffdingTree : public BinaryTree<Node<Data>> {
  public:
    void infer(typename Data::datatype data[]);
    void train(typename Data::datatype data[]);

  protected:
    const float _errorMargin = 0;
    uint splitAttribute = 0;
    uint splitValue = 0; // <
};

#endif
