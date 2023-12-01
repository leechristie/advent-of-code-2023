// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <ctype.h>

#include "puzzle.h"
#include "day01.h"

static int parse_two_digits(int, int);

void solve01(void) {

    FILE * file = open_input_file(1);

    unsigned int answer1 = 0;
    char firstDigit = '\0';
    char lastDigit = '\0';
    int c;
    do {
        c = fgetc(file);
        if (c == '\n') {
            if (firstDigit) {
                answer1 += parse_two_digits(firstDigit, lastDigit);
                firstDigit = '\0';
                lastDigit = '\0';
            }
        } else if (c != EOF) {
            if (isdigit(c)) {
                if (!firstDigit) {
                    firstDigit = (char) c;
                }
                lastDigit = (char) c;
            }
        }
    } while ((char) c != EOF);

    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 1\n");
    printf("Part 1: %d\n", answer1);
    printf("Part 2: TODO\n");

}

static int parse_two_digits(int firstDigit, int lastDigit) {
    return 10 * (firstDigit - '0') + (lastDigit - '0');
}
