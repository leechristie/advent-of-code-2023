// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <fstream>
#include <vector>
#include "puzzle.hpp"

std::ifstream get_puzzle_input(int day) {
    std::string filename = (day < 10)
                      ? "../../input/input0" + std::to_string(day) + ".txt"
                      : "../../input/input" + std::to_string(day) + ".txt";
    std::ifstream rv {filename};
    if (!rv)
        throw std::ios_base::failure("unable to read input file");
    return rv;
}

std::vector<std::string> get_puzzle_lines(int day) {
    std::ifstream in = get_puzzle_input(day);
    std::vector<std::string> rv{};
    std::string line;
    while (true) {
        std::getline(in, line);
        if (line.empty())
            return rv;
        rv.push_back(line);
    }
}