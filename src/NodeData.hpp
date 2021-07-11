#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <cmath>
#include <stdlib.h>
#include <sys/types.h>
#include <tuple>

#include "TopSplitBuffer.hpp"

template <typename T_datatype = float, uint T_N_Attributes = 16,
          uint T_N_Classes = 2, uint T_N_Quantiles = 8, uint T_N_pt = 10>
class NodeData {
  public:
    typedef T_datatype datatype;
    static const uint N_Attributes = T_N_Attributes;
    static const uint N_Classes = T_N_Classes;
    static const uint N_Quantiles = T_N_Quantiles;
    static const uint N_pt = T_N_pt;

    typedef datatype (*sampleScaler)(datatype);

    enum AttibuteRange { Min = 0, Max = 1 };
    enum SplitType { Left = 0, Right = 1, None };

    NodeData(datatype lambda = 0.01) : _lambda(lambda) {}

    constexpr uint getSampleCountTotal() { return _sampleCountTotal; }

    constexpr uint getSampleCountPerClass(uint classif) {
        return _sampleCountPerClass[classif];
    }

    void update(datatype sample[N_Attributes], uint classif) {

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

    datatype getConfidence() {
        return (datatype)_sampleCountPerClass[_mostCommonClass] /
               _sampleCountTotal;
    }

    constexpr datatype getImpurity() { return _gini(NULL, NULL, None); }

    std::tuple<uint, datatype, datatype> evaluateSplit() {
        TopSplitBuffer<2, datatype> topSplitCandidates;

        for (uint i = 0; i < N_Attributes; i++) {

            datatype dist[N_Classes][2], distSum[2] = {0};

            for (uint p = 0; p < N_pt; p++) {
                datatype pt = _getSplitPointValue(i, p);
                for (uint j = 0; j < N_Classes; j++) {
                    uint distL, distR;
                    std::tie(distL, distR) =
                        _getSampleCountDistribuition(i, j, pt);

                    dist[j][Left] = distL;
                    dist[j][Right] = distR;

                    distSum[Left] += distL;
                }
                distSum[Right] = getSampleCountTotal() - distSum[Left];

                datatype G_pt = _G(dist, distSum);
                topSplitCandidates.add(i, pt, G_pt);
            }
        }

        std::tuple<uint, datatype, datatype> top =
            topSplitCandidates.getCandidate(0);
        std::get<2>(top) -= topSplitCandidates.getG(1);

        return top;
    }

  protected:
    uint _mostCommonClass = 0;
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

    constexpr void _updateQuantiles(uint attributeIndex, uint classif,
                                    datatype value) {
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
        distL = std::round((datatype)distL / N_pt) *
                _sampleCountPerClass[classIndex];
        uint distR = _sampleCountPerClass[classIndex] - distL;

        return {distL, distR};
    }

    constexpr datatype _classImpurity(uint j) {
        if (!_sampleCountTotal) {
            return 0;
        }
        return (datatype)_sampleCountPerClass[j] / _sampleCountTotal;
    }

    constexpr datatype _prob(datatype (*dist)[2], datatype *distSum,
                             SplitType X, uint j) {
        return dist[j][X] / distSum[X];
    }

    constexpr datatype _gini(datatype (*dist)[2], datatype *distSum,
                             SplitType X) {
        datatype ret = 1;
        for (uint j = 0; j < N_Classes; j++) {
            datatype p;
            if (X == None) {
                p = _classImpurity(j);
            } else {
                p = _prob(dist, distSum, X, j);
            }
            ret -= std::pow(p, 2);
        }
        return ret;
    }

    constexpr datatype _weightedGini(datatype (*dist)[2], datatype *distSum,
                                     SplitType X) {
        return (distSum[X] / _sampleCountTotal) * _gini(dist, distSum, X);
    }

    constexpr datatype _G(datatype (*dist)[2], datatype *distSum) {
        return _gini(dist, distSum, None) - _weightedGini(dist, distSum, Left) -
               _weightedGini(dist, distSum, Right);
    }
};

#endif
