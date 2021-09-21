# Hoeffding-Tree

A C/C++ HLS-ready implementation of a Hoeffding Tree.

Statistical storage in nodes is made through quantile estimation using assymetric signum functions. Derived from the work of Lin et al.

## Recomended HLS kernel

```C++
//#define USE_XILINX_AP_TYPES

#include "HoeffdingTree.hpp"

#define ATTRIBUTES 16
#define CLASSES 2
#define NODES 127
#define SAMPLE_ARRAY_SIZE 10000

typedef HoeffdingTree<Node<NodeData<float,      // datatype
                                    ATTRIBUTES, // Attributes
                                    CLASSES     // Classes
                                    >,
                           NODES // Node upperbound
                           >>
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

extern "C" {

void krnl_Tree(Tree *tree, Sample<Tree> sample[SAMPLE_ARRAY_SIZE], Prediction<Tree> prediction[SAMPLE_ARRAY_SIZE], unsigned int bundleSize) {

	sample_loop: for (unsigned int i = 0; i < bundleSize; i++) {
		if (sample[i]->doSplitTrial) {
			std::tie(prediction[i]->classification, prediction[i]->confidence) =
				tree->train(sample[i]->data, sample[i]->classification, true);
		} else {
			std::tie(prediction[i]->classification, prediction[i]->confidence) =
				tree->infer(sample[i]->data);
		}
	}
}

}
```
