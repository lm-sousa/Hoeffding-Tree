#ifndef __TYPE_CHOOSER_HPP__
#define __TYPE_CHOOSER_HPP__

#include <cstdint>
#include <type_traits>

#ifdef USE_XILINX_AP_TYPES
#include "ap_int.h"

#define TypeChooser_Unsigned(MaxValue) std::conditional < MaxValue< 2, ap_uint<1>, \
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

#else
#define TypeChooser_Unsigned(MaxValue)                                         \
    std::conditional < MaxValue < 256U, uint8_t,                               \
        std::conditional <                                                     \
            MaxValue<65536U, uint16_t,                                         \
                     std::conditional<MaxValue<4294967296U, uint32_t,          \
                                               uint64_t>::type>::type>::type
#endif

#define TypeChooser_Signed(MinValue, MaxValue) a

#endif
