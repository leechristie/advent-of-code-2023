// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <string>
#include <iostream>

#include "days.hpp"

int main(int argc, char * argv[]) {

    if (argc != 2) {
        std::cout << "Valid day not specified in command line argument." << std::endl;
        return 1;
    }
    
    switch (std::stoi(std::string(argv[1]))) {
        case 1:
            solve01();
            break;
        case 2:
            solve02();
            break;
        case 9:
            solve09();
            break;
        default:
            std::cout << "Valid day not specified in command line argument." << std::endl;
            return 1;
    }
    return 0;

}
