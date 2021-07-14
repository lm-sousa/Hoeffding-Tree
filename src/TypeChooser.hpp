#ifndef __TYPE_CHOOSER_HPP__
#define __TYPE_CHOOSER_HPP__

#include <cstdint>
#include <type_traits>

#ifdef USE_XILINX_AP_TYPES
#include "ap_int.h"

#define TypeChooser_Unsigned(MaxValue)                                         \
std::conditional < MaxValue< 2, ap_uint<1>, \
std::conditional < MaxValue< 4U, ap_uint<2>, \
std::conditional < MaxValue< 8U, ap_uint<3>, \
std::conditional < MaxValue< 16U,    ap_uint<4>, \
std::conditional < MaxValue< 32U,    ap_uint<5>, \
std::conditional < MaxValue< 64U,    ap_uint<6>, \
std::conditional < MaxValue< 128U,   ap_uint<7>, \
std::conditional < MaxValue< 256U,   ap_uint<8>, \
std::conditional < MaxValue< 512U,   ap_uint<9>, \
std::conditional < MaxValue< 1024U,  ap_uint<10>, \
std::conditional < MaxValue< 2048U,  ap_uint<11>, \
std::conditional < MaxValue< 4096U,  ap_uint<12>, \
std::conditional < MaxValue< 8192U,  ap_uint<13>, \
std::conditional < MaxValue< 16384U, ap_uint<14>, \
std::conditional < MaxValue< 32768U, ap_uint<15>, \
std::conditional < MaxValue< 65536U, ap_uint<16>, \
std::conditional < MaxValue< 131072U,    ap_uint<17>, \
std::conditional < MaxValue< 262144U,    ap_uint<18>, \
std::conditional < MaxValue< 524288U,    ap_uint<19>, \
std::conditional < MaxValue< 1048576U,   ap_uint<20>, \
std::conditional < MaxValue< 2097152U,   ap_uint<21>, \
std::conditional < MaxValue< 4194304U,   ap_uint<22>, \
std::conditional < MaxValue< 8388608U,   ap_uint<23>, \
std::conditional < MaxValue< 16777216U,  ap_uint<24>, \
std::conditional < MaxValue< 33554432U,  ap_uint<25>, \
std::conditional < MaxValue< 67108864U,  ap_uint<26>, \
std::conditional < MaxValue< 134217728U, ap_uint<27>, \
std::conditional < MaxValue< 268435456U, ap_uint<28>, \
std::conditional < MaxValue< 536870912U, ap_uint<29>, \
std::conditional < MaxValue< 1073741824U,    ap_uint<30>, \
std::conditional < MaxValue< 2147483648U,    ap_uint<31>, \
std::conditional < MaxValue< 4294967296U,    ap_uint<32>, \
std::conditional < MaxValue< 8589934592U,    ap_uint<33>, \
std::conditional < MaxValue< 17179869184U,   ap_uint<34>, \
std::conditional < MaxValue< 34359738368U,   ap_uint<35>, \
std::conditional < MaxValue< 68719476736U,   ap_uint<36>, \
std::conditional < MaxValue< 137438953472U,  ap_uint<37>, \
std::conditional < MaxValue< 274877906944U,  ap_uint<38>, \
std::conditional < MaxValue< 549755813888U,  ap_uint<39>, \
std::conditional < MaxValue< 1099511627776U, ap_uint<40>, \
std::conditional < MaxValue< 2199023255552U, ap_uint<41>, \
std::conditional < MaxValue< 4398046511104U, ap_uint<42>, \
std::conditional < MaxValue< 8796093022208U, ap_uint<43>, \
std::conditional < MaxValue< 17592186044416U,    ap_uint<44>, \
std::conditional < MaxValue< 35184372088832U,    ap_uint<45>, \
std::conditional < MaxValue< 70368744177664U,    ap_uint<46>, \
std::conditional < MaxValue< 140737488355328U,   ap_uint<47>, \
std::conditional < MaxValue< 281474976710656U,   ap_uint<48>, \
std::conditional < MaxValue< 562949953421312U,   ap_uint<49>, \
std::conditional < MaxValue< 1125899906842624U,  ap_uint<50>, \
std::conditional < MaxValue< 2251799813685248U,  ap_uint<51>, \
std::conditional < MaxValue< 4503599627370496U,  ap_uint<52>, \
std::conditional < MaxValue< 9007199254740990U,  ap_uint<53>, \
std::conditional < MaxValue< 18014398509482000U, ap_uint<54>, \
std::conditional < MaxValue< 36028797018964000U, ap_uint<55>, \
std::conditional < MaxValue< 72057594037927900U, ap_uint<56>, \
std::conditional < MaxValue< 144115188075856000U,    ap_uint<57>, \
std::conditional < MaxValue< 288230376151712000U,    ap_uint<58>, \
std::conditional < MaxValue< 576460752303424000U,    ap_uint<59>, \
std::conditional < MaxValue< 1152921504606850000U,   ap_uint<60>, \
std::conditional < MaxValue< 2305843009213690000U,   ap_uint<61>, \
std::conditional < MaxValue< 4611686018427390000U,   ap_uint<62>, \
std::conditional < MaxValue< 9223372036854780000U,   ap_uint<63>, ap_uint<64> \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type

#define TypeChooser_Signed(MinValue, MaxValue)                                                                  \
std::conditional < (MinValue>= -1                   && MaxValue<= 0 ), ap_int<1>, \
std::conditional < (MinValue>= -2                   && MaxValue<= 1 ), ap_int<2>, \
std::conditional < (MinValue>= -4                   && MaxValue<= 3 ), ap_int<3>, \
std::conditional < (MinValue>= -8                   && MaxValue<= 7 ), ap_int<4>, \
std::conditional < (MinValue>= -16                  && MaxValue<= 15 ), ap_int<5>, \
std::conditional < (MinValue>= -32                  && MaxValue<= 31 ), ap_int<6>, \
std::conditional < (MinValue>= -64                  && MaxValue<= 63 ), ap_int<7>, \
std::conditional < (MinValue>= -128                 && MaxValue<= 127 ), ap_int<8>, \
std::conditional < (MinValue>= -256                 && MaxValue<= 255 ), ap_int<9>, \
std::conditional < (MinValue>= -512                 && MaxValue<= 511 ), ap_int<10>, \
std::conditional < (MinValue>= -1024                && MaxValue<= 1023 ), ap_int<11>, \
std::conditional < (MinValue>= -2048                && MaxValue<= 2047 ), ap_int<12>, \
std::conditional < (MinValue>= -4096                && MaxValue<= 4095 ), ap_int<13>, \
std::conditional < (MinValue>= -8192                && MaxValue<= 8191 ), ap_int<14>, \
std::conditional < (MinValue>= -16384               && MaxValue<= 16383 ), ap_int<15>, \
std::conditional < (MinValue>= -32768               && MaxValue<= 32767 ), ap_int<16>, \
std::conditional < (MinValue>= -65536               && MaxValue<= 65535 ), ap_int<17>, \
std::conditional < (MinValue>= -131072              && MaxValue<= 131071 ), ap_int<18>, \
std::conditional < (MinValue>= -262144              && MaxValue<= 262143 ), ap_int<19>, \
std::conditional < (MinValue>= -524288              && MaxValue<= 524287 ), ap_int<20>, \
std::conditional < (MinValue>= -1048576             && MaxValue<= 1048575 ), ap_int<21>, \
std::conditional < (MinValue>= -2097152             && MaxValue<= 2097151 ), ap_int<22>, \
std::conditional < (MinValue>= -4194304             && MaxValue<= 4194303 ), ap_int<23>, \
std::conditional < (MinValue>= -8388608             && MaxValue<= 8388607 ), ap_int<24>, \
std::conditional < (MinValue>= -16777216            && MaxValue<= 16777215 ), ap_int<25>, \
std::conditional < (MinValue>= -33554432            && MaxValue<= 33554431 ), ap_int<26>, \
std::conditional < (MinValue>= -67108864            && MaxValue<= 67108863 ), ap_int<27>, \
std::conditional < (MinValue>= -134217728           && MaxValue<= 134217727 ), ap_int<28>, \
std::conditional < (MinValue>= -268435456           && MaxValue<= 268435455 ), ap_int<29>, \
std::conditional < (MinValue>= -536870912           && MaxValue<= 536870911 ), ap_int<30>, \
std::conditional < (MinValue>= -1073741824          && MaxValue<= 1073741823 ), ap_int<31>, \
std::conditional < (MinValue>= -2147483648          && MaxValue<= 2147483647 ), ap_int<32>, \
std::conditional < (MinValue>= -4294967296          && MaxValue<= 4294967295 ), ap_int<33>, \
std::conditional < (MinValue>= -8589934592          && MaxValue<= 8589934591 ), ap_int<34>, \
std::conditional < (MinValue>= -17179869184         && MaxValue<= 17179869183 ), ap_int<35>, \
std::conditional < (MinValue>= -34359738368         && MaxValue<= 34359738367 ), ap_int<36>, \
std::conditional < (MinValue>= -68719476736         && MaxValue<= 68719476735 ), ap_int<37>, \
std::conditional < (MinValue>= -137438953472        && MaxValue<= 137438953471 ), ap_int<38>, \
std::conditional < (MinValue>= -274877906944        && MaxValue<= 274877906943 ), ap_int<39>, \
std::conditional < (MinValue>= -549755813888        && MaxValue<= 549755813887 ), ap_int<40>, \
std::conditional < (MinValue>= -1099511627776       && MaxValue<= 1099511627775 ), ap_int<41>, \
std::conditional < (MinValue>= -2199023255552       && MaxValue<= 2199023255551 ), ap_int<42>, \
std::conditional < (MinValue>= -4398046511104       && MaxValue<= 4398046511103 ), ap_int<43>, \
std::conditional < (MinValue>= -8796093022208       && MaxValue<= 8796093022207 ), ap_int<44>, \
std::conditional < (MinValue>= -17592186044416      && MaxValue<= 17592186044415 ), ap_int<45>, \
std::conditional < (MinValue>= -35184372088832      && MaxValue<= 35184372088831 ), ap_int<46>, \
std::conditional < (MinValue>= -70368744177664      && MaxValue<= 70368744177663 ), ap_int<47>, \
std::conditional < (MinValue>= -140737488355328     && MaxValue<= 140737488355327 ), ap_int<48>, \
std::conditional < (MinValue>= -281474976710656     && MaxValue<= 281474976710655 ), ap_int<49>, \
std::conditional < (MinValue>= -562949953421312     && MaxValue<= 562949953421311 ), ap_int<50>, \
std::conditional < (MinValue>= -1125899906842624    && MaxValue<= 1125899906842623 ), ap_int<51>, \
std::conditional < (MinValue>= -2251799813685248    && MaxValue<= 2251799813685247 ), ap_int<52>, \
std::conditional < (MinValue>= -4503599627370496    && MaxValue<= 4503599627370495 ), ap_int<53>, \
std::conditional < (MinValue>= -9007199254740990    && MaxValue<= 9007199254740991 ), ap_int<54>, \
std::conditional < (MinValue>= -18014398509482000   && MaxValue<= 18014398509482000 ), ap_int<55>, \
std::conditional < (MinValue>= -36028797018964000   && MaxValue<= 36028797018964000 ), ap_int<56>, \
std::conditional < (MinValue>= -72057594037927900   && MaxValue<= 72057594037927900 ), ap_int<57>, \
std::conditional < (MinValue>= -144115188075856000  && MaxValue<= 144115188075856000 ), ap_int<58>, \
std::conditional < (MinValue>= -288230376151712000  && MaxValue<= 288230376151712000 ), ap_int<59>, \
std::conditional < (MinValue>= -576460752303424000  && MaxValue<= 576460752303424000 ), ap_int<60>, \
std::conditional < (MinValue>= -1152921504606850000 && MaxValue<= 1152921504606850000 ), ap_int<61>, \
std::conditional < (MinValue>= -2305843009213690000 && MaxValue<= 2305843009213690000 ), ap_int<62>, \
std::conditional < (MinValue>= -4611686018427390000 && MaxValue<= 4611686018427390000 ), ap_int<63>, ap_int<64> \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type

#else // ifdef USE_XILINX_AP_TYPES

#define TypeChooser_Unsigned(MaxValue)                                         \
    std::conditional < MaxValue < 256U, uint8_t,                               \
        std::conditional <                                                     \
            MaxValue<65536U, uint16_t,                                         \
                     std::conditional<MaxValue<4294967296U, uint32_t,          \
                                               uint64_t>::type>::type>::type

#define TypeChooser_Signed(MinValue, MaxValue)                                 \
    std::conditional<                                                          \
        (MinValue >= -128 && MaxValue <= 127), int8_t,                         \
        std::conditional<(MinValue >= -32768 && MaxValue <= 32767), int16_t,   \
                         std::conditional<(MinValue >= -2147483648 &&          \
                                           MaxValue <= 2147483647),            \
                                          int32_t, int64_t>::type>::type>::    \
        type

#endif // ifdef USE_XILINX_AP_TYPES

#endif
