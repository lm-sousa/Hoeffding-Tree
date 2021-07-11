#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <cmath>
#include <stdlib.h>
#include <sys/types.h>
#include <tuple>

#include "TopSplitBuffer.hpp"
#include "TypeChooser.hpp"

template <
    typename datatype_T = float,
    typename attribute_index_T = TypeChooser_Unsigned(16),
    uint32_t N_Attributes_T = 16,
    typename class_index_T = TypeChooser_Unsigned(2), uint32_t N_Classes_T = 2,
    typename quantile_index_T = TypeChooser_Unsigned(8),
    uint32_t N_Quantiles_T = 8,
    typename point_index_T = TypeChooser_Unsigned(10), uint32_t N_pt_T = 10>
class NodeData {
  public:
    typedef datatype_T data_t;
    typedef attribute_index_T attribute_index_t;
    typedef class_index_T class_index_t;
    typedef quantile_index_T quantile_index_t;
    typedef point_index_T point_index_t;
    static const uint N_Attributes = N_Attributes_T;
    static const uint N_Classes = N_Classes_T;
    static const uint N_Quantiles = N_Quantiles_T;
    static const uint N_pt = N_pt_T;

    typedef data_t (*sampleScaler)(data_t);

    enum AttibuteRange { Min = 0, Max = 1 };
    enum SplitType { Left = 0, Right = 1, None };

    NodeData(data_t lambda = 0.01) : _lambda(lambda) {}

    constexpr uint getSampleCountTotal() { return _sampleCountTotal; }

    constexpr uint getSampleCountPerClass(uint classif) {
        return _sampleCountPerClass[classif];
    }

    void update(data_t sample[N_Attributes], uint classif) {

        for (uint i = 0; i < N_Attributes; i++) {
            _updateAttributeRange(i, sample[i]);

            _updateQuantiles(i, classif, sample[i]);
        }

        _sampleCountTotal++;
        _sampleCountPerClass[classif]++;

        if (_sampleCountPerClass[classif] >
            _sampleCountPerClass[_mostCommonClass]) {
            _mostCommonClass = classif;
        }
    }

    uint getMostCommonClass() { return _mostCommonClass; }

    data_t getConfidence() {
        return (data_t)_sampleCountPerClass[_mostCommonClass] /
               _sampleCountTotal;
    }

    constexpr data_t getImpurity() { return _gini(NULL, NULL, None); }

    std::tuple<uint, data_t, data_t> evaluateSplit() {
        TopSplitBuffer<2, data_t> topSplitCandidates;

        for (uint i = 0; i < N_Attributes; i++) {

            data_t dist[N_Classes][2], distSum[2] = {0};

            for (uint p = 0; p < N_pt; p++) {
                data_t pt = _getSplitPointValue(i, p);
                for (uint j = 0; j < N_Classes; j++) {
                    uint distL, distR;
                    std::tie(distL, distR) =
                        _getSampleCountDistribuition(i, j, pt);

                    dist[j][Left] = distL;
                    dist[j][Right] = distR;

                    distSum[Left] += distL;
                }
                distSum[Right] = getSampleCountTotal() - distSum[Left];

                data_t G_pt = _G(dist, distSum);
                topSplitCandidates.add(i, pt, G_pt);
            }
        }

        std::tuple<uint, data_t, data_t> top =
            topSplitCandidates.getCandidate(0);
        std::get<2>(top) -= topSplitCandidates.getG(1);

        return top;
    }

  protected:
    uint _mostCommonClass = 0;
    uint _sampleCountTotal = 0;
    uint _sampleCountPerClass[N_Classes] = {0};
    data_t _Attributes[N_Attributes][N_Classes][N_Quantiles] = {0};
    data_t _attributeRanges[N_Attributes][2] = {0};

    const data_t _lambda;

    /**
     * @brief Asymmetric signum function
     *
     * @param z
     * @return constexpr datatype
     */
    constexpr data_t _sgnAlpha(data_t z, data_t alpha) {
        return z < 0 ? (-alpha) : (1 - alpha);
    }

    constexpr data_t _getAlphaFromQuantileIndex(uint quantileIndex) {
        return (data_t)(quantileIndex + 1) / (N_Quantiles + 1);
    }

    void _updateAttributeRange(uint attributeIndex, data_t value) {
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

    constexpr void _updateQuantiles(uint attributeIndex, uint classif,
                                    data_t value) {
        for (uint k = 0; k < N_Quantiles; k++) {
            _Attributes[attributeIndex][classif][k] -=
                _lambda *
                _sgnAlpha(_Attributes[attributeIndex][classif][k] - value,
                          _getAlphaFromQuantileIndex(k));
        }
    }

    constexpr data_t _getSplitPointValue(uint attributeIndex, uint p) {
        return ((_attributeRanges[attributeIndex][AttibuteRange::Max] -
                 _attributeRanges[attributeIndex][AttibuteRange::Min]) /
                (N_pt + 1)) *
                   p +
               _attributeRanges[attributeIndex][AttibuteRange::Min];
    }

    constexpr std::tuple<uint, uint>
    _getSampleCountDistribuition(uint attributeIndex, uint classIndex,
                                 data_t pt) {
        uint distL = 0;
        for (uint k = 0; k < N_Quantiles; k++) {
            if (pt > _Attributes[attributeIndex][classIndex][k])
                distL++;
        }
        distL =
            std::round((data_t)distL / N_pt) * _sampleCountPerClass[classIndex];
        uint distR = _sampleCountPerClass[classIndex] - distL;

        return {distL, distR};
    }

    constexpr data_t _classImpurity(uint j) {
        if (!_sampleCountTotal) {
            return 0;
        }
        return (data_t)_sampleCountPerClass[j] / _sampleCountTotal;
    }

    constexpr data_t _prob(data_t (*dist)[2], data_t *distSum, SplitType X,
                           uint j) {
        return dist[j][X] / distSum[X];
    }

    constexpr data_t _gini(data_t (*dist)[2], data_t *distSum, SplitType X) {
        data_t ret = 1;
        for (uint j = 0; j < N_Classes; j++) {
            data_t p;
            if (X == None) {
                p = _classImpurity(j);
            } else {
                p = _prob(dist, distSum, X, j);
            }
            ret -= std::pow(p, 2);
        }
        return ret;
    }

    constexpr data_t _weightedGini(data_t (*dist)[2], data_t *distSum,
                                   SplitType X) {
        return (distSum[X] / _sampleCountTotal) * _gini(dist, distSum, X);
    }

    constexpr data_t _G(data_t (*dist)[2], data_t *distSum) {
        return _gini(dist, distSum, None) - _weightedGini(dist, distSum, Left) -
               _weightedGini(dist, distSum, Right);
    }
};

#endif
