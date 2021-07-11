#include "TypeChooser.hpp"

TypeChooser_Unsigned(100) a = 100;
std::conditional<100 < 256, uint8_t, uint16_t>::type b = 100;
auto c = 100;

typedef TypeChooser_Unsigned(100) index_t;

index_t d = 100;
