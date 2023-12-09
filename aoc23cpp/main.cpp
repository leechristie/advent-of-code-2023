// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <string>
#include <iostream>

#include "day01.hpp"

int main(int argc, char * argv[]) {

    if (argc != 2 || std::string(argv[1]) != "1") {
        std::cout << "Valid day not specified in command line argument." << std::endl;
        return 1;
    }

    solve01();

    return 0;

}
