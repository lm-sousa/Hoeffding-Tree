#include "config.hpp"

// extern "C" {

void krnl_Tree(Tree *tree, Sample<Tree> sample[SAMPLE_ARRAY_SIZE],
               Prediction<Tree> prediction[SAMPLE_ARRAY_SIZE],
               uint32_t bundleSize) {

sample_loop:
    for (uint32_t i = 0; i < bundleSize; i++) {
        if (sample[i].doSplitTrial) {
            std::tie(prediction[i].classification, prediction[i].confidence) =
                tree->train(sample[i].data, sample[i].classification, true);
        } else {
            std::tie(prediction[i].classification, prediction[i].confidence) =
                tree->infer(sample[i].data);
        }
    }
}
//}
