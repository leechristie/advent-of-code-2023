// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

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

std::vector<int> space_split_int(std::string const &line) {
    std::vector<int> rv;
    std::istringstream stream(line);
    int value;
    while (stream >> value)
        rv.push_back(value);
    return rv;
}

std::vector<int> reverse(std::vector<int> const &forward) {
    std::vector<int> rv;
    rv.reserve(forward.size());
    for (int i = (int) forward.size() - 1; i >= 0; i--)
        rv.push_back(forward.at(i));
    return rv;
}

void print_vector(std::string const &name, std::vector<int> const &vec) {
    std::cout << name << " = [";
    for (int i = 0; i < (int) vec.size(); i++) {
        if (i != 0)
            std::cout << ", ";
        std::cout << vec.at(i);
    }
    std::cout << "]\n";
}

void check(long expected, long actual) {
    if (expected != actual)
        throw std::runtime_error(
                "expected: " + std::to_string(expected)
                + ", actual: " + std::to_string(actual));
}
