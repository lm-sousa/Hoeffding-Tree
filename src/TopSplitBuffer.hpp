#ifndef __TOP_BUFFER_HPP__
#define __TOP_BUFFER_HPP__

#include <stdlib.h>
#include <tuple>

template <uint T_size, typename _datatype> class TopSplitBuffer {

  public:
    typedef _datatype datatype;

    bool add(uint attributeIndex, datatype splitValue, datatype G) {
        for (uint i = 0; i < T_size; i++) {
            if (G > this->G[i]) {
                for (uint j = T_size - 1; j > i; j--) {
                    _updateCandidate(j, this->attributeIndex[j - 1],
                                     this->splitValue[j - 1], this->G[j - 1]);
                }
                _updateCandidate(i, attributeIndex, splitValue, G);
                return true;
            }
        }
        return false;
    }

    constexpr std::tuple<uint, datatype, datatype> getCandidate(uint index) {
        return {attributeIndex[index], splitValue[index], G[index]};
    }

    constexpr datatype getG(uint index) { return G[index]; }

  private:
    uint attributeIndex[T_size] = {0};
    datatype splitValue[T_size] = {0};
    datatype G[T_size] = {0};

    void _updateCandidate(uint index, uint attributeIndex, datatype splitValue,
                          datatype giniImpurity) {
        this->attributeIndex[index] = attributeIndex;
        this->splitValue[index] = splitValue;
        this->G[index] = giniImpurity;
    }
};

#endif
