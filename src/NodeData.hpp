#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <cmath>
#include <stdlib.h>
#include <sys/types.h>
#include <tuple>

#include "TopSplitBuffer.hpp"
#include "TypeChooser.hpp"
#include "TypeChooserMath.hpp"

template <typename datatype_T = float, uint N_Attributes_T = 16,
          uint N_Classes_T = 2, uint N_Quantiles_T = 8, uint N_pt_T = 10,
          typename sample_count_T = uint>
class NodeData {
  public:
    typedef datatype_T data_t;
    typedef TypeChooser_Unsigned(N_Attributes_T) attribute_index_t;
    typedef TypeChooser_Unsigned(N_Classes_T) class_index_t;
    typedef TypeChooser_Unsigned(N_Quantiles_T) quantile_index_t;
    typedef TypeChooser_Unsigned(N_pt_T) point_index_t;
    typedef sample_count_T sample_count_t;
    static const uint N_Attributes = N_Attributes_T;
    static const uint N_Classes = N_Classes_T;
    static const uint N_Quantiles = N_Quantiles_T;
    static const uint N_pt = N_pt_T;

    typedef data_t (*sampleScaler)(data_t);

    enum AttributeRange { Min = 0, Max = 1 };
    enum SplitType { Left = 0, Right = 1, None };

    NodeData(data_t lambda = 0.01) : _lambda(lambda) {}

    sample_count_t getSampleCountTotal() { return _sampleCountTotal; }

    sample_count_t getSampleCountPerClass(class_index_t classif) {
        return _sampleCountPerClass[classif];
    }

    void update(data_t sample[N_Attributes], class_index_t classif) {

    NodeData_update__attributes:
        for (attribute_index_t i = 0; i < N_Attributes; i++) {
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

    class_index_t getMostCommonClass() { return _mostCommonClass; }

    data_t getConfidence() {
        return (data_t)_sampleCountPerClass[_mostCommonClass] /
               _sampleCountTotal;
    }

    data_t getImpurity() { return _gini(NULL, NULL, None); }

    std::tuple<bool, attribute_index_t, data_t, data_t> evaluateSplit() {
        TopSplitBuffer<2, data_t, attribute_index_t> topSplitCandidates;

    NodeData_evaluateSplit__attributes:
        for (attribute_index_t i = 0; i < N_Attributes; i++) {
        NodeData_evaluateSplit__attributes__pt:
            for (point_index_t p = 0; p < N_pt; p++) {
                sample_count_t dist[N_Classes][2], distSum[2] = {0};

                data_t pt = _getSplitPointValue(i, p);
            NodeData_evaluateSplit__attributes__pt__classes:
                for (class_index_t j = 0; j < N_Classes; j++) {
#pragma HLS unroll
                    sample_count_t distL, distR;
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

        std::tuple<bool, attribute_index_t, data_t, data_t> top =
            topSplitCandidates.getCandidate(0);
        std::get<3>(top) -= topSplitCandidates.getG(1);

        return top;
    }

  protected:
    class_index_t _mostCommonClass = 0;
    sample_count_t _sampleCountTotal = 0;
    sample_count_t _sampleCountPerClass[N_Classes] = {0};
    data_t _Attributes[N_Attributes][N_Classes][N_Quantiles] = {{{0}}};
    data_t _attributeRanges[N_Attributes][2] = {{0}};

    const data_t _lambda;

    /**
     * @brief Asymmetric signum function
     *
     * @param z
     * @return datatype
     */
    data_t _sgnAlpha(data_t z, data_t alpha) {
        return z < 0 ? (-alpha) : ((data_t)1 - alpha);
    }

    data_t _getAlphaFromQuantileIndex(quantile_index_t quantileIndex) {
        return (data_t)(quantileIndex + 1) / (N_Quantiles + 1);
    }

    void _updateAttributeRange(attribute_index_t attributeIndex, data_t value) {
        if (_sampleCountTotal) {
            if (value < _attributeRanges[attributeIndex][AttributeRange::Min]) {
                _attributeRanges[attributeIndex][AttributeRange::Min] = value;
            }

            if (value > _attributeRanges[attributeIndex][AttributeRange::Max]) {
                _attributeRanges[attributeIndex][AttributeRange::Max] = value;
            }
        } else {
            _attributeRanges[attributeIndex][AttributeRange::Min] = value;
            _attributeRanges[attributeIndex][AttributeRange::Max] = value;
        }
    }

    void _updateQuantiles(attribute_index_t attributeIndex,
                          class_index_t classif, data_t value) {
    NodeData_updateQuantiles__quantiles:
        for (quantile_index_t k = 0; k < N_Quantiles; k++) {
            _Attributes[attributeIndex][classif][k] -=
                _lambda *
                _sgnAlpha(_Attributes[attributeIndex][classif][k] - value,
                          _getAlphaFromQuantileIndex(k));
        }
    }

    data_t _getSplitPointValue(attribute_index_t attributeIndex,
                               point_index_t p) {
        return ((_attributeRanges[attributeIndex][AttributeRange::Max] -
                 _attributeRanges[attributeIndex][AttributeRange::Min]) /
                (N_pt + 1)) *
                   p +
               _attributeRanges[attributeIndex][AttributeRange::Min];
    }

    std::tuple<sample_count_t, sample_count_t>
    _getSampleCountDistribuition(attribute_index_t attributeIndex,
                                 class_index_t classIndex, data_t splitPoint) {
        sample_count_t distL = 0;
    NodeData_getSampleCountDistribuition__quantiles:
        for (quantile_index_t k = 0; k < N_Quantiles; k++) {
            if (splitPoint > _Attributes[attributeIndex][classIndex][k]) {
                distL++;
            } else {
                break;
            }
        }
        distL = tcm::round(((data_t)distL / N_pt) *
                           _sampleCountPerClass[classIndex]);
        sample_count_t distR = _sampleCountPerClass[classIndex] - distL;

        return {distL, distR};
    }

    data_t _classImpurity(class_index_t j) {
        if (!_sampleCountTotal) {
            return 0;
        }
        return (data_t)_sampleCountPerClass[j] / _sampleCountTotal;
    }

    data_t _prob(sample_count_t (*dist)[2], sample_count_t *distSum,
                 SplitType X, class_index_t j) {
        if (!distSum[X]) {
            return 0;
        }

        // std::cout << dist[j][X] << "/" << distSum[X] << std::endl;
        return (data_t)dist[j][X] / distSum[X];
    }

    data_t _gini(sample_count_t (*dist)[2], sample_count_t *distSum,
                 SplitType X) {
        data_t ret = 1;
    NodeData_gini__classes:
        for (class_index_t j = 0; j < N_Classes; j++) {
            data_t p = 0;
            if (X == None) {
                p = _classImpurity(j);
            } else {
                p = _prob(dist, distSum, X, j);
            }
            ret -= tcm::pow(p, 2);
        }
        return ret;
    }

    data_t _weightedGini(sample_count_t (*dist)[2], sample_count_t *distSum,
                         SplitType X) {
        if (!_sampleCountTotal) {
            return 0;
        }

        return ((data_t)distSum[X] / _sampleCountTotal) *
               _gini(dist, distSum, X);
    }

    data_t _G(sample_count_t (*dist)[2], sample_count_t *distSum) {
        return _gini(dist, distSum, None) - _weightedGini(dist, distSum, Left) -
               _weightedGini(dist, distSum, Right);
    }
};

#endif
