#include <iostream>

#include "Binary.hpp"

#include "CBenchmark.hpp"

BENCHMARKING("E:/binary.json");
int main()
{
    TRACE;
    Binary bin;
    std::cout << "Enter the bits:" << std::endl;
    std::cin >> bin;
    std::cout << bin << std::endl;
    return 0;
}
