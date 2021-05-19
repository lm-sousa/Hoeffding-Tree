#include "NodeData.hpp"

#include <math.h>

void NodeData::update(datatype data[]) {
    _sampleCount++;
    bool homogeneous = false;

    for (uint i = 0; i < _nAttributes; i++) {
        _attributes_count[i] += data[i];
        if (_attributes_count[i] == _sampleCount) {
            homogeneous = true;
        }
    }

    if (!homogeneous) {
        // calculate G for every attribute
        // Calculate _hoeffdingBound()
    }
}

constexpr uint NodeData::sgnAlpha(datatype z, float alpha) {
    return z < 0 ? alpha : 1 - alpha;
}

float NodeData::_hoeffdingBound(const uint r, const float sigma, uint n) {
    return (r * (sqrt(-log(sigma) / 2))) / sqrt(n);
}

constexpr float NodeData::_CMA(float CMA_n, uint n_1, float x_n_1) {
    return CMA_n + ((x_n_1 - CMA_n) / (n_1));
}
