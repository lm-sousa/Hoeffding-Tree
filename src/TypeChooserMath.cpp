#include "TypeChooserMath.hpp"

namespace tcm {

float round(float x) { return std::round(x); }
float pow(float x, float y) { return std::pow(x, y); }
float sqrt(float x) { return std::sqrt(x); }
float log(float x) { return std::log(x); }

double round(double x) { return std::round(x); }
double pow(double x, double y) { return std::pow(x, y); }
double sqrt(double x) { return std::sqrt(x); }
double log(double x) { return std::log(x); }

} // namespace tcm
