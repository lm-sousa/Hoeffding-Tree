#ifndef __TYPE_CHOOSER_HPP__
#define __TYPE_CHOOSER_HPP__

#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <type_traits>

template <uintmax_t N> constexpr uintmax_t log2_floor() {
    if (N == 0) {
        return 0;
    }

    uintmax_t result = 0;
    uintmax_t N_ = N;
    for (; N_ > 1; N_ >>= 1) {
        ++result;
    }
    return result;
}

template <uintmax_t N> constexpr uintmax_t log2_ceil() {
    if (N == 0) {
        return 0;
    }

    return log2_floor<N>() + 1;
}

static_assert(log2_floor<1>() == 0, "log2_floor<1>() != 0");
static_assert(log2_floor<2>() == 1, "log2_floor<2>() != 1");
static_assert(log2_floor<4>() == 2, "log2_floor<4>() != 2");
static_assert(log2_floor<8>() == 3, "log2_floor<8>() != 3");
static_assert(log2_floor<16>() == 4, "log2_floor<16>() != 4");
static_assert(log2_floor<32>() == 5, "log2_floor<33>() != 5");
static_assert(log2_floor<64>() == 6, "log2_floor<64>() != 6");
static_assert(log2_floor<128>() == 7, "log2_floor<128>() != 7");
static_assert(log2_floor<256>() == 8, "log2_floor<256>() != 8");

static_assert(log2_floor<3>() == 1, "log2_floor<3>() != 1");
static_assert(log2_floor<7>() == 2, "log2_floor<7>() != 2");
static_assert(log2_floor<15>() == 3, "log2_floor<15>() != 3");
static_assert(log2_floor<31>() == 4, "log2_floor<31>() != 4");
static_assert(log2_floor<63>() == 5, "log2_floor<63>() != 5");
static_assert(log2_floor<127>() == 6, "log2_floor<127>() != 6");
static_assert(log2_floor<255>() == 7, "log2_floor<255>() != 7");

static_assert(log2_ceil<1>() == 1, "log2_ceil<1>() != 1");
static_assert(log2_ceil<2>() == 2, "log2_ceil<2>() != 2");
static_assert(log2_ceil<4>() == 3, "log2_ceil<4>() != 3");
static_assert(log2_ceil<8>() == 4, "log2_ceil<8>() != 4");
static_assert(log2_ceil<16>() == 5, "log2_ceil<16>() != 5");
static_assert(log2_ceil<32>() == 6, "log2_ceil<32>() != 6");
static_assert(log2_ceil<64>() == 7, "log2_ceil<64>() != 7");
static_assert(log2_ceil<128>() == 8, "log2_ceil<128>() != 8");
static_assert(log2_ceil<256>() == 9, "log2_ceil<256>() != 9");

static_assert(log2_ceil<3>() == 2, "log2_ceil<3>() != 2");
static_assert(log2_ceil<7>() == 3, "log2_ceil<7>() != 3");
static_assert(log2_ceil<15>() == 4, "log2_ceil<15>() != 4");
static_assert(log2_ceil<31>() == 5, "log2_ceil<31>() != 5");
static_assert(log2_ceil<63>() == 6, "log2_ceil<63>() != 6");
static_assert(log2_ceil<127>() == 7, "log2_ceil<127>() != 7");
static_assert(log2_ceil<255>() == 8, "log2_ceil<255>() != 8");

#ifdef USE_XILINX_AP_TYPES
#include "ap_int.h"

template <uintmax_t MaxValue> using TCU = ap_uint<log2_ceil<MaxValue>()>;
template <intmax_t MinValue, intmax_t MaxValue>
using TCS =
    ap_int<std::max(log2_ceil < MinValue < 0 ? -MinValue : MinValue > (),
                    log2_ceil < MaxValue < 0 ? -MaxValue : MaxValue > ()) +
           1>;

#else // ifdef USE_XILINX_AP_TYPES

template <uintmax_t numberOfBits_T> struct AP_UINT {
    using type = typename std::conditional<
        (numberOfBits_T <= 8), uint8_t,
        typename std::conditional<
            (numberOfBits_T <= 16), uint16_t,
            typename std::conditional<(numberOfBits_T <= 32), uint32_t,
                                      uint64_t>::type>::type>::type;
};

template <intmax_t numberOfBits_T> struct AP_INT {
    using type = typename std::conditional<
        (numberOfBits_T <= 8), int8_t,
        typename std::conditional<
            (numberOfBits_T <= 16), int16_t,
            typename std::conditional<(numberOfBits_T <= 32), int32_t,
                                      int64_t>::type>::type>::type;
};
template <uintmax_t MaxValue>
using TCU = typename AP_UINT<log2_ceil<MaxValue>()>::type;
template <intmax_t MinValue, intmax_t MaxValue>
using TCS =
    typename AP_INT<std::max(
                        log2_ceil < MinValue < 0 ? -MinValue : MinValue > (),
                        log2_ceil < MaxValue < 0 ? -MaxValue : MaxValue > ()) +
                    1>::type;

static_assert(
    std::is_same<TCU<std::numeric_limits<uint8_t>::max()>, uint8_t>::value,
    "TCU<uint8_MAX>::type != uint8_t");
static_assert(
    std::is_same<TCU<std::numeric_limits<uint8_t>::max() + 1>, uint16_t>::value,
    "TCU<uint8_MAX + 1>::type != uint16_t");

static_assert(
    std::is_same<TCS<0, std::numeric_limits<int8_t>::max()>, int8_t>::value,
    "TCS<0, 127>::type != int8_t");

static_assert(std::is_same<TCS<0, std::numeric_limits<int8_t>::max() + 1>,
                           int16_t>::value,
              "TCS<0, 128>::type != int16_t");

static_assert(
    std::is_same<TCS<std::numeric_limits<int8_t>::min() + 1, 0>, int8_t>::value,
    "TCS<-127, 0>::type != int8_t");

static_assert(
    std::is_same<TCS<std::numeric_limits<int8_t>::min(), 0>, int16_t>::value,
    "TCS<-128, 0>::type != int16_t");

static_assert(std::is_same<TCS<std::numeric_limits<int8_t>::min() - 1, 0>,
                           int16_t>::value,
              "TCS<-129, 0>::type != int16_t");

#endif // ifdef USE_XILINX_AP_TYPES
#endif
