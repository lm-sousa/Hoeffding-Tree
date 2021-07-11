#ifndef __TYPE_CHOOSER_HPP__
#define __TYPE_CHOOSER_HPP__

#include <cstdint>
#include <type_traits>

#define USE_XILINX_AP_TYPES

#ifdef USE_XILINX_AP_TYPES
#include "ap_int.h"

#define TypeChooser_Unsigned(MaxValue) std::conditional < MaxValue<	2	, ap_int<	1	>, \
std::conditional < MaxValue<	4	, ap_int<	2	>, \
std::conditional < MaxValue<	8	, ap_int<	3	>, \
std::conditional < MaxValue<	16	, ap_int<	4	>, \
std::conditional < MaxValue<	32	, ap_int<	5	>, \
std::conditional < MaxValue<	64	, ap_int<	6	>, \
std::conditional < MaxValue<	128	, ap_int<	7	>, \
std::conditional < MaxValue<	256	, ap_int<	8	>, \
std::conditional < MaxValue<	512	, ap_int<	9	>, \
std::conditional < MaxValue<	1024	, ap_int<	10	>, \
std::conditional < MaxValue<	2048	, ap_int<	11	>, \
std::conditional < MaxValue<	4096	, ap_int<	12	>, \
std::conditional < MaxValue<	8192	, ap_int<	13	>, \
std::conditional < MaxValue<	16384	, ap_int<	14	>, \
std::conditional < MaxValue<	32768	, ap_int<	15	>, \
std::conditional < MaxValue<	65536	, ap_int<	16	>, \
std::conditional < MaxValue<	131072	, ap_int<	17	>, \
std::conditional < MaxValue<	262144	, ap_int<	18	>, \
std::conditional < MaxValue<	524288	, ap_int<	19	>, \
std::conditional < MaxValue<	1048576	, ap_int<	20	>, \
std::conditional < MaxValue<	2097152	, ap_int<	21	>, \
std::conditional < MaxValue<	4194304	, ap_int<	22	>, \
std::conditional < MaxValue<	8388608	, ap_int<	23	>, \
std::conditional < MaxValue<	16777216	, ap_int<	24	>, \
std::conditional < MaxValue<	33554432	, ap_int<	25	>, \
std::conditional < MaxValue<	67108864	, ap_int<	26	>, \
std::conditional < MaxValue<	134217728	, ap_int<	27	>, \
std::conditional < MaxValue<	268435456	, ap_int<	28	>, \
std::conditional < MaxValue<	536870912	, ap_int<	29	>, \
std::conditional < MaxValue<	1073741824	, ap_int<	30	>, \
std::conditional < MaxValue<	2147483648	, ap_int<	31	>, \
std::conditional < MaxValue<	4294967296	, ap_int<	32	>, \
std::conditional < MaxValue<	8589934592	, ap_int<	33	>, \
std::conditional < MaxValue<	17179869184	, ap_int<	34	>, \
std::conditional < MaxValue<	34359738368	, ap_int<	35	>, \
std::conditional < MaxValue<	68719476736	, ap_int<	36	>, \
std::conditional < MaxValue<	137438953472	, ap_int<	37	>, \
std::conditional < MaxValue<	274877906944	, ap_int<	38	>, \
std::conditional < MaxValue<	549755813888	, ap_int<	39	>, \
std::conditional < MaxValue<	1099511627776	, ap_int<	40	>, \
std::conditional < MaxValue<	2199023255552	, ap_int<	41	>, \
std::conditional < MaxValue<	4398046511104	, ap_int<	42	>, \
std::conditional < MaxValue<	8796093022208	, ap_int<	43	>, \
std::conditional < MaxValue<	17592186044416	, ap_int<	44	>, \
std::conditional < MaxValue<	35184372088832	, ap_int<	45	>, \
std::conditional < MaxValue<	70368744177664	, ap_int<	46	>, \
std::conditional < MaxValue<	140737488355328	, ap_int<	47	>, \
std::conditional < MaxValue<	281474976710656	, ap_int<	48	>, \
std::conditional < MaxValue<	562949953421312	, ap_int<	49	>, \
std::conditional < MaxValue<	1125899906842624	, ap_int<	50	>, \
std::conditional < MaxValue<	2251799813685248	, ap_int<	51	>, \
std::conditional < MaxValue<	4503599627370496	, ap_int<	52	>, \
std::conditional < MaxValue<	9007199254740990	, ap_int<	53	>, \
std::conditional < MaxValue<	18014398509482000	, ap_int<	54	>, \
std::conditional < MaxValue<	36028797018964000	, ap_int<	55	>, \
std::conditional < MaxValue<	72057594037927900	, ap_int<	56	>, \
std::conditional < MaxValue<	144115188075856000	, ap_int<	57	>, \
std::conditional < MaxValue<	288230376151712000	, ap_int<	58	>, \
std::conditional < MaxValue<	576460752303424000	, ap_int<	59	>, \
std::conditional < MaxValue<	1152921504606850000	, ap_int<	60	>, \
std::conditional < MaxValue<	2305843009213690000	, ap_int<	61	>, \
std::conditional < MaxValue<	4611686018427390000	, ap_int<	62	>,  \
std::conditional < MaxValue<	9223372036854780000	, ap_int<	63	>,  \
std::conditional < MaxValue<	18446744073709600000, ap_int<	64	>, ap_int<65> \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
>::type \
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
    std::conditional < MaxValue < 256, uint8_t,                                \
        std::conditional <                                                     \
            MaxValue<65536, uint16_t,                                          \
                     std::conditional<MaxValue<4294967296, uint32_t,           \
                                               uint64_t>::type>::type>::type
#endif

#define TypeChooser_Signed(MinValue, MaxValue) a

#endif
