#ifndef __HOEFFDING_TREE_HPP__
#define __HOEFFDING_TREE_HPP__

#include "BinaryTree.hpp"

#ifndef HT_DATA_ATTRIBUTES_N
#define HT_DATA_ATTRIBUTES_N 1
#endif
class HoeffdingTree : public BinaryTree {
  public:
    class Data {
      public:
        typedef bool datatype;
        void update(datatype data[]);

      protected:
        uint _attributes_count[HT_DATA_ATTRIBUTES_N] = {0};
        uint _sampleCount = 0;
        static const uint _nAttributes = HT_DATA_ATTRIBUTES_N;

        /**
         * @brief Calculates the Hoeffding Bound
         *
         * @param r Range of variable
         * @param sigma acceptable error margin (0.0 to 1.0)
         * @param n_samples Number of samples in the leaf node
         * @return float Hoeffding bound
         */
        static float _hoeffdingBound(uint r, uint sigma, uint n_samples);

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

    void infer(Data::datatype data[]);
    void train(Data::datatype data[]);

  protected:
    float _errorMargin = 0;
};

#endif
