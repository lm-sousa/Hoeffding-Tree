
#define USE_XILINX_AP_TYPES

#include "TypeChooser.hpp"

// int main(int argc, char **argv) {
int main() {
    typedef TypeChooser_Unsigned(1000) index_t;
    index_t a(1000);

    int b(100);
    std::cout << a << ", " << b << std::endl;
    std::cout << std::hex << a << std::endl;
    std::cout << std::hex << b << std::endl;
}
