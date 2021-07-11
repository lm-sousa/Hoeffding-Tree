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

#define TypeChooser_Signed(MinValue, MaxValue)                                                                        \
std::conditional < (MinValue>= -1LL && MaxValue<= 0LL ), ap_int<1>, \
std::conditional < (MinValue>= -2LL && MaxValue<= 1LL ), ap_int<2>, \
std::conditional < (MinValue>= -4LL && MaxValue<= 3LL ), ap_int<3>, \
std::conditional < (MinValue>= -8LL && MaxValue<= 7LL ), ap_int<4>, \
std::conditional < (MinValue>= -16LL    && MaxValue<= 15LL ), ap_int<5>, \
std::conditional < (MinValue>= -32LL    && MaxValue<= 31LL ), ap_int<6>, \
std::conditional < (MinValue>= -64LL    && MaxValue<= 63LL ), ap_int<7>, \
std::conditional < (MinValue>= -128LL   && MaxValue<= 127LL ), ap_int<8>, \
std::conditional < (MinValue>= -256LL   && MaxValue<= 255LL ), ap_int<9>, \
std::conditional < (MinValue>= -512LL   && MaxValue<= 511LL ), ap_int<10>, \
std::conditional < (MinValue>= -1024LL  && MaxValue<= 1023LL ), ap_int<11>, \
std::conditional < (MinValue>= -2048LL  && MaxValue<= 2047LL ), ap_int<12>, \
std::conditional < (MinValue>= -4096LL  && MaxValue<= 4095LL ), ap_int<13>, \
std::conditional < (MinValue>= -8192LL  && MaxValue<= 8191LL ), ap_int<14>, \
std::conditional < (MinValue>= -16384LL && MaxValue<= 16383LL ), ap_int<15>, \
std::conditional < (MinValue>= -32768LL && MaxValue<= 32767LL ), ap_int<16>, \
std::conditional < (MinValue>= -65536LL && MaxValue<= 65535LL ), ap_int<17>, \
std::conditional < (MinValue>= -131072LL    && MaxValue<= 131071LL ), ap_int<18>, \
std::conditional < (MinValue>= -262144LL    && MaxValue<= 262143LL ), ap_int<19>, \
std::conditional < (MinValue>= -524288LL    && MaxValue<= 524287LL ), ap_int<20>, \
std::conditional < (MinValue>= -1048576LL   && MaxValue<= 1048575LL ), ap_int<21>, \
std::conditional < (MinValue>= -2097152LL   && MaxValue<= 2097151LL ), ap_int<22>, \
std::conditional < (MinValue>= -4194304LL   && MaxValue<= 4194303LL ), ap_int<23>, \
std::conditional < (MinValue>= -8388608LL   && MaxValue<= 8388607LL ), ap_int<24>, \
std::conditional < (MinValue>= -16777216LL  && MaxValue<= 16777215LL ), ap_int<25>, \
std::conditional < (MinValue>= -33554432LL  && MaxValue<= 33554431LL ), ap_int<26>, \
std::conditional < (MinValue>= -67108864LL  && MaxValue<= 67108863LL ), ap_int<27>, \
std::conditional < (MinValue>= -134217728LL && MaxValue<= 134217727LL ), ap_int<28>, \
std::conditional < (MinValue>= -268435456LL && MaxValue<= 268435455LL ), ap_int<29>, \
std::conditional < (MinValue>= -536870912LL && MaxValue<= 536870911LL ), ap_int<30>, \
std::conditional < (MinValue>= -1073741824LL    && MaxValue<= 1073741823LL ), ap_int<31>, \
std::conditional < (MinValue>= -2147483648LL    && MaxValue<= 2147483647LL ), ap_int<32>, \
std::conditional < (MinValue>= -4294967296LL    && MaxValue<= 4294967295LL ), ap_int<33>, \
std::conditional < (MinValue>= -8589934592LL    && MaxValue<= 8589934591LL ), ap_int<34>, \
std::conditional < (MinValue>= -17179869184LL   && MaxValue<= 17179869183LL ), ap_int<35>, \
std::conditional < (MinValue>= -34359738368LL   && MaxValue<= 34359738367LL ), ap_int<36>, \
std::conditional < (MinValue>= -68719476736LL   && MaxValue<= 68719476735LL ), ap_int<37>, \
std::conditional < (MinValue>= -137438953472LL  && MaxValue<= 137438953471LL ), ap_int<38>, \
std::conditional < (MinValue>= -274877906944LL  && MaxValue<= 274877906943LL ), ap_int<39>, \
std::conditional < (MinValue>= -549755813888LL  && MaxValue<= 549755813887LL ), ap_int<40>, \
std::conditional < (MinValue>= -1099511627776LL && MaxValue<= 1099511627775LL ), ap_int<41>, \
std::conditional < (MinValue>= -2199023255552LL && MaxValue<= 2199023255551LL ), ap_int<42>, \
std::conditional < (MinValue>= -4398046511104LL && MaxValue<= 4398046511103LL ), ap_int<43>, \
std::conditional < (MinValue>= -8796093022208LL && MaxValue<= 8796093022207LL ), ap_int<44>, \
std::conditional < (MinValue>= -17592186044416LL    && MaxValue<= 17592186044415LL ), ap_int<45>, \
std::conditional < (MinValue>= -35184372088832LL    && MaxValue<= 35184372088831LL ), ap_int<46>, \
std::conditional < (MinValue>= -70368744177664LL    && MaxValue<= 70368744177663LL ), ap_int<47>, \
std::conditional < (MinValue>= -140737488355328LL   && MaxValue<= 140737488355327LL ), ap_int<48>, \
std::conditional < (MinValue>= -281474976710656LL   && MaxValue<= 281474976710655LL ), ap_int<49>, \
std::conditional < (MinValue>= -562949953421312LL   && MaxValue<= 562949953421311LL ), ap_int<50>, \
std::conditional < (MinValue>= -1125899906842624LL  && MaxValue<= 1125899906842623LL ), ap_int<51>, \
std::conditional < (MinValue>= -2251799813685248LL  && MaxValue<= 2251799813685247LL ), ap_int<52>, \
std::conditional < (MinValue>= -4503599627370496LL  && MaxValue<= 4503599627370495LL ), ap_int<53>, \
std::conditional < (MinValue>= -9007199254740990LL  && MaxValue<= 9007199254740991LL ), ap_int<54>, \
std::conditional < (MinValue>= -18014398509482000LL && MaxValue<= 18014398509482000LL ), ap_int<55>, \
std::conditional < (MinValue>= -36028797018964000LL && MaxValue<= 36028797018964000LL ), ap_int<56>, \
std::conditional < (MinValue>= -72057594037927900LL && MaxValue<= 72057594037927900LL ), ap_int<57>, \
std::conditional < (MinValue>= -144115188075856000LL    && MaxValue<= 144115188075856000LL ), ap_int<58>, \
std::conditional < (MinValue>= -288230376151712000LL    && MaxValue<= 288230376151712000LL ), ap_int<59>, \
std::conditional < (MinValue>= -576460752303424000LL    && MaxValue<= 576460752303424000LL ), ap_int<60>, \
std::conditional < (MinValue>= -1152921504606850000LL   && MaxValue<= 1152921504606850000LL ), ap_int<61>, \
std::conditional < (MinValue>= -2305843009213690000LL   && MaxValue<= 2305843009213690000LL ), ap_int<62>, \
std::conditional < (MinValue>= -4611686018427390000LL   && MaxValue<= 4611686018427390000LL ), ap_int<63>, ap_int<64> \
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
        (MinValue >= -128LL && MaxValue <= 127LL), int8_t,                     \
        std::conditional<                                                      \
            (MinValue >= -32768LL && MaxValue <= 32767LL), int16_t,            \
            std::conditional<(MinValue >= -2147483648LL &&                     \
                              MaxValue <= 2147483647LL),                       \
                             int32_t, int64_t>::type>::type>::type
#endif // ifdef USE_XILINX_AP_TYPES

#endif
