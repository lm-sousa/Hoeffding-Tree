#ifndef __TOP_BUFFER_HPP__
#define __TOP_BUFFER_HPP__

#include <stdlib.h>
#include <tuple>

template <uint size_T, typename data_T> class TopSplitBuffer {

  public:
    typedef data_T data_t;

    bool add(uint attributeIndex, data_t splitValue, data_t G) {
        for (uint i = 0; i < size_T; i++) {
            if (G > this->G[i]) {
                for (uint j = size_T - 1; j > i; j--) {
                    _updateCandidate(j, this->attributeIndex[j - 1],
                                     this->splitValue[j - 1], this->G[j - 1]);
                }
                _updateCandidate(i, attributeIndex, splitValue, G);
                return true;
            }
        }
        return false;
    }

    constexpr std::tuple<uint, data_t, data_t> getCandidate(uint index) {
        return {attributeIndex[index], splitValue[index], G[index]};
    }

    constexpr data_t getG(uint index) { return G[index]; }

  private:
    uint attributeIndex[size_T] = {0};
    data_t splitValue[size_T] = {0};
    data_t G[size_T] = {0};

    void _updateCandidate(uint index, uint attributeIndex, data_t splitValue,
                          data_t giniImpurity) {
        this->attributeIndex[index] = attributeIndex;
        this->splitValue[index] = splitValue;
        this->G[index] = giniImpurity;
    }
};

#endif
