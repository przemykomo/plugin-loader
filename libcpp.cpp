#include <iostream>

extern "C" void init() {
    std::cout << "Library C++ init" << std::endl;
}
