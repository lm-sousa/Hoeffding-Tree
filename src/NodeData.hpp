#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <stdlib.h>
#include <sys/types.h>

template <typename _datatype = float, uint N_Attributes = 16,
          uint N_Classes = 2, uint N_Quantiles = 8>
class NodeData {
  public:
    typedef _datatype datatype;

    NodeData(float alpha = 0, float lambda = 0.01)
        : _alpha(alpha), _lambda(lambda) {}

    /**
     * @brief Asymmetric signum function
     *
     * @param z
     * @return constexpr uint
     */
    constexpr uint sgnAlpha(datatype z) { return z < 0 ? -_alpha : 1 - _alpha; }

    void update(datatype data[], uint classification) {

        _sampleCountTotal++;
        _sampleCountPerClass[classification]++;

        for (uint i = 0; i < N_Attributes; i++) {
            if (data[i] < _attributeRanges[i][AttibuteRange::Min]) {
                _attributeRanges[i][AttibuteRange::Min] = data[i];
            }

            if (data[i] > _attributeRanges[i][AttibuteRange::Max]) {
                _attributeRanges[i][AttibuteRange::Max] = data[i];
            }

            for (uint k = 0; k < N_Quantiles; k++) {
                _Attributes[i][classification][k] -=
                    _lambda *
                    sgnAlpha(_Attributes[i][classification][k] - data[i]);
            }
        }
    }

    enum AttibuteRange { Min = 0, Max = 1 };

  protected:
    uint _sampleCountTotal = 0;
    uint _sampleCountPerClass[N_Classes] = {0};
    datatype _Attributes[N_Attributes][N_Classes][N_Quantiles] = {0};
    datatype _attributeRanges[N_Attributes][2] = {0};

    const float _alpha, _lambda;
};

#endif
