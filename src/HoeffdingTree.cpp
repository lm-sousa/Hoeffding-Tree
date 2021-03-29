#include "HoeffdingTree.hpp"

#include <math.h>

void HoeffdingTree::Data::update(datatype data[]) {
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

float HoeffdingTree::Data::_hoeffdingBound(uint range, uint confidence,
                                           uint n_samples) {
    return sqrt(((range * range) * log(1 / confidence)) / (2 * n_samples));
}

constexpr float HoeffdingTree::Data::_CMA(float CMA_n, uint n_1, float x_n_1) {
    return CMA_n + ((x_n_1 - CMA_n) / (n_1));
}

void HoeffdingTree::infer(Data::datatype data[]) {}

void HoeffdingTree::train(Data::datatype data[]) {}
