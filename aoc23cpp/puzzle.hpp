// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23CPP_PUZZLE_HPP
#define AOC23CPP_PUZZLE_HPP

#include <fstream>
#include <vector>

std::ifstream get_puzzle_input(int);
std::vector<std::string> get_puzzle_lines(int);
std::vector<int> space_split_int(std::string const &);
std::vector<int> reverse(std::vector<int> const &);
void print_vector(std::string const &, std::vector<int> const &);
void check(long, long);

#endif //AOC23CPP_PUZZLE_HPP
