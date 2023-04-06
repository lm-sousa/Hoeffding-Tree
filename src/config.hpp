#ifndef __HOEFFDING_TREE_CONFIG_HPP__
#define __HOEFFDING_TREE_CONFIG_HPP__

// #define USE_XILINX_AP_TYPES

#include "HoeffdingTree.hpp"

#define DATATYPE float
#define ATTRIBUTES 4
#define CLASSES 3
#define NODES 127
#define SAMPLE_ARRAY_SIZE 150

typedef HoeffdingTree<Node<NodeData<DATATYPE,   // datatype
                                    ATTRIBUTES, // Attributes
                                    CLASSES     // Classes
                                    >>,
                      NODES /*Node upperbound*/>
    Tree;

typedef Tree::data_t data_t;

template <class T> struct Prediction {
    typename T::class_index_t classification;
    typename T::data_t confidence;
};

template <class T> struct Sample {
    typename T::data_t data[T::_DataClass::N_Attributes];
    typename T::class_index_t classification;
    bool doSplitTrial;
};

#endif // __HOEFFDING_TREE_CONFIG_HPP__
