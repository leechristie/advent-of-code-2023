// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "puzzle.hpp"

std::ifstream get_input_stream(int day) {
    std::string filename = (day < 10)
                      ? "../../input/input0" + std::to_string(day) + ".txt"
                      : "../../input/input" + std::to_string(day) + ".txt";
    std::ifstream in {filename};
    if (!in)
        throw std::ios_base::failure("unable to read input file");
    return in;
}
