// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <iostream>
#include <numeric>

#include "puzzle.hpp"

static void extrapolate_pass(std::vector<int> &values, int bound) {
    bool encountered_non_zero = false;
    for (int i = 0; i <= bound - 2; i++) {
        values[i] = values[i + 1] - values[i];
        if (values[i] != 0)
            encountered_non_zero = true;
    }
    if (encountered_non_zero)
        extrapolate_pass(values, bound - 1);
}

static int extrapolate(std::vector<int> &values) {
    extrapolate_pass(values, (int) values.size());
    return std::accumulate(values.begin(),
                           values.end(),
                           0);
}

void solve09() {

    std::cout << "Advent of Code 2023" << std::endl;
    std::cout << "Day 9" << std::endl;

    int answer1 = 0;
    int answer2 = 0;
    for (auto &line : get_puzzle_lines(9)) {
        std::vector<int> forwards = space_split_int(line);
        std::vector<int> backwards = reverse(forwards);
        answer1 += extrapolate(forwards);
        answer2 += extrapolate(backwards);
    }

    std::cout << "Part 1: " << answer1 << "\n";
    check(1972648895, answer1);
    std::cout << "Part 2: " << answer2 << "\n";
    check(919, answer2);

}
