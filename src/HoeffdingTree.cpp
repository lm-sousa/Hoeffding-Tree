#include "HoeffdingTree.hpp"

#include <math.h>

HoeffdingTree::ReturnCode HoeffdingTree::infer() { return ReturnCode::ERROR; }

HoeffdingTree::ReturnCode HoeffdingTree::train() { return ReturnCode::ERROR; }

float HoeffdingTree::_hoeffdingBound(uint range, uint confidence,
                                     uint n_samples) {
    return sqrt(((range * range) * log(1 / confidence)) / (2 * n_samples));
}