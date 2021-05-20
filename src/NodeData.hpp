#ifndef __NODE_DATA_HPP__
#define __NODE_DATA_HPP__

#include <stdlib.h>
#include <sys/types.h>

template <typename _datatype = float, uint N_Attributes = 1> class NodeData {
  public:
    typedef _datatype datatype;
    void update(datatype data[]) {
        _sampleCount++;
        bool homogeneous = false;

        for (uint i = 0; i < N_Attributes; i++) {
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

  protected:
    uint _attributes_count[N_Attributes] = {0};
    uint _sampleCount = 0;
};

#endif
