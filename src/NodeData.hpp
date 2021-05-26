#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <stdlib.h>
#include <sys/types.h>
#include <tuple>

template <typename _datatype = float, uint N_Attributes = 16,
          uint N_Classes = 2, uint N_Quantiles = 8, uint N_pt = 10>
class NodeData {
  public:
    typedef _datatype datatype;

    enum AttibuteRange { Min = 0, Max = 1 };

    NodeData(datatype lambda = 0.01) : _lambda(lambda) {}

    uint getSampleCountTotal() { return _sampleCountTotal; }

    uint getSampleCountPerClass(uint classif) {
        return _sampleCountPerClass[classif];
    }

    void update(datatype sample[], uint classif) {

        for (uint i = 0; i < N_Attributes; i++) {
            _updateAttributeRange(i, sample[i]);

            _updateQuantiles(i, classif, sample[i]);
        }

        _sampleCountTotal++;
        _sampleCountPerClass[classif]++;
    }

    void spliTrial() {
        for (uint i = 0; i < N_Attributes; i++) {
            for (uint p = 0; p < N_pt; p++) {
                datatype pt = _getSplitPointValue(i, p);
                for (uint j = 1; j < N_Classes; j++) {
                    uint distL, distR;
                    std::tie(distL, distR) =
                        _getSampleCountDistribuition(i, j, pt);
                }
            }
            // Compute G(ai) for all pt
        }
        // Check hoeffding bound stuff
    }

  protected:
    uint _sampleCountTotal = 0;
    uint _sampleCountPerClass[N_Classes] = {0};
    datatype _Attributes[N_Attributes][N_Classes][N_Quantiles] = {0};
    datatype _attributeRanges[N_Attributes][2] = {0};

    const datatype _lambda;

    /**
     * @brief Asymmetric signum function
     *
     * @param z
     * @return constexpr datatype
     */
    constexpr datatype _sgnAlpha(datatype z, datatype alpha) {
        return z < 0 ? (-alpha) : (1 - alpha);
    }

    constexpr datatype _getAlphaFromQuantileIndex(uint quantileIndex) {
        return (datatype)(quantileIndex + 1) / (N_Quantiles + 1);
    }

    void _updateAttributeRange(uint attributeIndex, datatype value) {
        if (_sampleCountTotal) {
            if (value < _attributeRanges[attributeIndex][AttibuteRange::Min]) {
                _attributeRanges[attributeIndex][AttibuteRange::Min] = value;
            }

            if (value > _attributeRanges[attributeIndex][AttibuteRange::Max]) {
                _attributeRanges[attributeIndex][AttibuteRange::Max] = value;
            }
        } else {
            _attributeRanges[attributeIndex][AttibuteRange::Min] = value;
            _attributeRanges[attributeIndex][AttibuteRange::Max] = value;
        }
    }

    void _updateQuantiles(uint attributeIndex, uint classif, datatype value) {
        for (uint k = 0; k < N_Quantiles; k++) {
            _Attributes[attributeIndex][classif][k] -=
                _lambda *
                _sgnAlpha(_Attributes[attributeIndex][classif][k] - value,
                          _getAlphaFromQuantileIndex(k));
        }
    }

    constexpr datatype _getSplitPointValue(uint attributeIndex, uint p) {
        return ((_attributeRanges[attributeIndex][AttibuteRange::Max] -
                 _attributeRanges[attributeIndex][AttibuteRange::Min]) /
                (N_pt + 1)) *
                   p +
               _attributeRanges[attributeIndex][AttibuteRange::Min];
    }

    constexpr std::tuple<uint, uint>
    _getSampleCountDistribuition(uint attributeIndex, uint classIndex,
                                 datatype pt) {
        uint distL = 0;
        for (uint k = 0; k < N_Quantiles; k++) {
            if (pt > _Attributes[attributeIndex][classIndex][k])
                distL++;
        }
        distL = ((datatype)distL / N_pt) * _sampleCountPerClass[classIndex];
        uint distR = _sampleCountPerClass[classIndex] - distL;

        return {distL, distR};
    }
};

#endif
