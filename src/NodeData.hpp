#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <stdlib.h>
#include <sys/types.h>

template <typename _datatype = float, uint N_Attributes = 1,
          uint N_Quantiles = 1>
class NodeData {
  public:
    typedef _datatype datatype;
    void update(datatype data[]) {
        _sampleCount++;
        bool homogeneous = false;

        for (uint i = 0; i < N_Attributes; i++) {
            _attributesCount[i] += data[i];
            if (_attributesCount[i] == _sampleCount) {
                homogeneous = true;
            }
        }

        if (!homogeneous) {
            // calculate G for every attribute
            // Calculate _hoeffdingBound()
        }
    }

  protected:
    uint _attributesCount[N_Attributes] = {0};
    uint _sampleCount = 0;
    datatype _Attributes[N_Attributes][N_Quantiles] = {0};
};

#endif
