// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <fstream>
#include <iostream>
#include <array>
#include "puzzle.hpp"
#include "days.hpp"

void read_basic_digit(std::string line, std::size_t beginIndex, char &firstDigit, char &lastDigit) {
    char c = line[beginIndex];
    if ('0' <= c && c <= '9') {
        lastDigit = c;
        if (!firstDigit)
            firstDigit = c;
    }
}

void read_spelled_digit(std::string line, std::size_t beginIndex, char &firstDigit, char &lastDigit) {

    static constexpr std::array<std::string, 10> WORDS {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    char c = line[beginIndex];
    if (c < '0' || '9' < c) {
        for (std::size_t j = 0; j < WORDS.size(); j++) {
            std::string digit = WORDS[j];
            std::size_t next = line.find(digit, beginIndex);
            if (next == beginIndex) {
                char cc = static_cast<char>(j + '0');
                lastDigit = cc;
                if (!firstDigit)
                    firstDigit = cc;
            }
        }
    }

}

void process_line(std::string line, int &answer1, int &answer2) {

    char firstBasicDigit = '\0';
    char lastBasicDigit = '\0';
    char firstDigit = '\0';
    char lastDigit = '\0';

    for (std::size_t beginIndex = 0; beginIndex < line.length(); beginIndex++) {

        read_basic_digit(line, beginIndex, firstDigit, lastDigit);
        read_basic_digit(line, beginIndex, firstBasicDigit, lastBasicDigit);

        read_spelled_digit(line, beginIndex, firstDigit, lastDigit);

    }

    std::string rv1;
    rv1 += firstBasicDigit;
    rv1 += lastBasicDigit;
    answer1 += stoi(rv1);

    std::string rv2;
    rv2 += firstDigit;
    rv2 += lastDigit;
    answer2 += stoi(rv2);

}

void solve01() {

    std::cout << "Advent of Code 2023" << std::endl;
    std::cout << "Day 1" << std::endl;

    std::ifstream in = get_puzzle_input(1);

    int answer1 = 0;
    int answer2 = 0;
    std::string line;
    while (in >> line)
        process_line(line, answer1, answer2);

    std::cout << "Part 1: " << answer1 << std::endl;
    std::cout << "Part 2: " << answer2 << std::endl;

}
