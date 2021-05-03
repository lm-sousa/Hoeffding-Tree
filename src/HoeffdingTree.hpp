#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include "BinaryTree.hpp"
#include "NodeData.hpp"
class HoeffdingTree : public BinaryTree {
  public:
    typedef Data NodeData;

    void infer(Data::datatype data[]);
    void train(Data::datatype data[]);

  protected:
    const float _errorMargin = 0;
    uint splitAttribute = 0;
    uint splitValue = 0; // <
};

#endif
