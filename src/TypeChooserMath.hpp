#ifndef __TYPE_CHOOSER_MATH_HPP__
#define __TYPE_CHOOSER_MATH_HPP__

#include "hls_math.h"
#include <cmath>

#include "ap_fixed.h"

namespace tcm {

template <class T> T makePrimitive(T x) { return x; }

float round(float x);
float pow(float x, float y);
float sqrt(float x);
float log(float x);

double round(double x);
double pow(double x, double y);
double sqrt(double x);
double log(double x);

template <int W, int I> double makePrimitive(ap_fixed<W, I> x) {
    return x.to_double();
}

template <int W, int I> ap_fixed<W, I> round(ap_fixed<W, I> x) {
    return hls::round(x);
}

template <int W, int I> ap_fixed<W, I> pow(ap_fixed<W, I> x, ap_fixed<W, I> y) {
    typedef ap_fixed<W, I> T;
    const T z = tcm::round(y);
    T w = 1;

TypeChooserMath_pow:
    for (uint i = 0; i < z; i++) {
#pragma HLS LOOP_TRIPCOUNT min = 0 max = z
        w *= x;
    }

    return w;
}

template <int W, int I, class T> ap_fixed<W, I> pow(ap_fixed<W, I> x, T y) {
    return tcm::pow(x, ap_fixed<W, I>(y));
}

template <int W, int I> ap_fixed<W, I> sqrt(ap_fixed<W, I> x) {
    return hls::sqrt(x);
}

// template <class T> T log(T x) {
template <int W, int I> ap_fixed<W, I> log(ap_fixed<W, I> x) {
    typedef ap_fixed<W, I> T;

    T y = 1 - x, z = -y;

TypeChooserMath_log:
    for (uint i = 2; i <= 6; i++) {
        z -= tcm::pow(y, i) / i;
    }

    return z;
}

} // namespace tcm

#endif
