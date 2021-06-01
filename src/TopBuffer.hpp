#ifndef __TOP_BUFFER_HPP__
#define __TOP_BUFFER_HPP__

#include <stdlib.h>

template <uint T_size, typename _datatype> class TopBuffer {

  public:
    typedef _datatype datatype;

    bool add(datatype x) {
        for (uint i = 0; i < T_size; i++) {
            if (x > elements[i]) {
                for (uint j = T_size - 1; j > i; j--) {
                    elements[j] = elements[j - 1];
                }
                elements[i] = x;
                return true;
            }
        }
        return false;
    }

    constexpr datatype get(uint index) { return elements[index]; }

  private:
    datatype elements[T_size] = {0};
};

#endif
