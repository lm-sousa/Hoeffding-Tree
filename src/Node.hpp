#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <stdlib.h>
#include <utility>

#include "NodeData.hpp"

template <class Data_T = NodeData<>> class Node {

  public:
    typedef Data_T _DataClass;
    typedef typename _DataClass::data_t data_t;
    typedef typename _DataClass::attribute_index_t attribute_index_t;
    typedef typename _DataClass::class_index_t class_index_t;
    typedef typename _DataClass::quantile_index_t quantile_index_t;
    typedef typename _DataClass::point_index_t point_index_t;
    typedef typename _DataClass::sample_count_t sample_count_t;

    /**
     * @brief Get the Data object
     *
     * @return void* Pointer to the Data object
     */
    _DataClass &getData() { return _data; }

    std::pair<class_index_t, data_t> infer() {
        return std::make_pair(getData().getMostCommonClass(),
                              getData().getConfidence());
    }

  private:
    _DataClass _data;

    // void _setParent(Node *parent) { _parent = parent; }
};

#endif
