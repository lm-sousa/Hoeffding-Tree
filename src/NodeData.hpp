#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <stdlib.h>
#include <sys/types.h>

template <typename _datatype = float, uint N_Attributes = 16,
          uint N_Classes = 2, uint N_Quantiles = 8, uint N_pt = 10>
class NodeData {
  public:
    typedef _datatype datatype;

    enum AttibuteRange { Min = 0, Max = 1 };

    NodeData(float alpha = 0, float lambda = 0.01)
        : _alpha(alpha), _lambda(lambda) {}

    /**
     * @brief Asymmetric signum function
     *
     * @param z
     * @return constexpr uint
     */
    constexpr uint sgnAlpha(datatype z) { return z < 0 ? -_alpha : 1 - _alpha; }

    uint getSampleCountTotal() { return _sampleCountTotal; }

    uint getSampleCountPerClass(uint classif) {
        return _sampleCountPerClass[classif];
    }

    void update(datatype sample[], uint classif) {

        _sampleCountTotal++;
        _sampleCountPerClass[classif]++;

        for (uint i = 0; i < N_Attributes; i++) {
            if (sample[i] < _attributeRanges[i][AttibuteRange::Min]) {
                _attributeRanges[i][AttibuteRange::Min] = sample[i];
            }

            if (sample[i] > _attributeRanges[i][AttibuteRange::Max]) {
                _attributeRanges[i][AttibuteRange::Max] = sample[i];
            }

            for (uint k = 0; k < N_Quantiles; k++) {
                _Attributes[i][classif][k] -=
                    _lambda * sgnAlpha(_Attributes[i][classif][k] - sample[i]);
            }
        }
    }

    constexpr datatype getSplitPointValue(uint attributeIndex, uint p) {
        return ((_attributeRanges[attributeIndex][AttibuteRange::Max] -
                 _attributeRanges[attributeIndex][AttibuteRange::Min]) /
                (N_pt + 1)) *
                   p +
               _attributeRanges[attributeIndex][AttibuteRange::Min];
    }

  protected:
    uint _sampleCountTotal = 0;
    uint _sampleCountPerClass[N_Classes] = {0};
    datatype _Attributes[N_Attributes][N_Classes][N_Quantiles] = {0};
    datatype _attributeRanges[N_Attributes][2] = {0};

    const float _alpha, _lambda;
};

#endif
