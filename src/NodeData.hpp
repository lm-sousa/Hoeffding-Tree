#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <stdlib.h>

#ifndef HT_DATA_ATTRIBUTES_N
#define HT_DATA_ATTRIBUTES_N 1
#endif

class Data {
  public:
    typedef float datatype;
    void update(datatype data[]);
    constexpr uint sgnAlpha(datatype z, float alpha);

  protected:
    uint _attributes_count[HT_DATA_ATTRIBUTES_N] = {0};
    uint _sampleCount = 0;
    static const uint _nAttributes = HT_DATA_ATTRIBUTES_N;

    /**
     * @brief Calculates the Hoeffding Bound
     *
     * @param r Range of variable
     * @param sigma acceptable error margin (0.0 to 1.0)
     * @param n Number of samples in the leaf node
     * @return float Hoeffding bound
     */
    static float _hoeffdingBound(const uint r, const float sigma, uint n);

    /**
     * @brief Cumulative Moving Average
     *
     * @param CMA_n Current CMA value
     * @param n_1 New sample count
     * @param x_n_1 New sample
     * @return constexpr float New CMA value
     */
    constexpr float _CMA(float CMA_n, uint n_1, float x_n_1);
};

#endif
