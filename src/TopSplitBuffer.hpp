#ifndef __TOP_BUFFER_HPP__
#define __TOP_BUFFER_HPP__

#include <stdlib.h>
#include <tuple>

template <uint size_T, typename data_T, typename attribute_index_T>
class TopSplitBuffer {

  public:
    typedef data_T data_t;
    typedef attribute_index_T attribute_index_t;

    bool add(attribute_index_t attributeIndex, data_t splitValue, data_t G) {
    TopSplitBuffer_add__size:
        for (attribute_index_t i = 0; i < size_T; i++) {
            if (G > this->G[i]) {
            TopSplitBuffer_add__size__size:
                for (attribute_index_t j = size_T - 1; j > i; j--) {
                    _updateCandidate(j, this->attributeIndex[j - 1],
                                     this->splitValue[j - 1], this->G[j - 1]);
                }
                _updateCandidate(i, attributeIndex, splitValue, G);
                return true;
            }
        }
        return false;
    }

    std::tuple<bool, attribute_index_t, data_t, data_t>
    getCandidate(attribute_index_t index) {
        return {isValid[index], attributeIndex[index], splitValue[index],
                G[index]};
    }

    data_t getG(attribute_index_t index) { return G[index]; }

  private:
    attribute_index_t attributeIndex[size_T] = {0};
    data_t splitValue[size_T] = {0};
    data_t G[size_T] = {0};
    bool isValid[size_T] = {false};

    void _updateCandidate(attribute_index_t index,
                          attribute_index_t attributeIndex, data_t splitValue,
                          data_t giniImpurity) {
        this->attributeIndex[index] = attributeIndex;
        this->splitValue[index] = splitValue;
        this->G[index] = giniImpurity;
        isValid[index] = true;
    }
};

#endif
