// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "day01.h"

void solve01(void) {

    unsigned int answer1 = 0;

    char * filename = "/Users/0x1ac/Developer/leechristie/advent-of-code-2023/input/input01.txt";
    FILE * file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open input file.\n");
        exit(1);
    }

    char firstDigit = '\0';
    char lastDigit = '\0';
    int c;
    do {
        c = fgetc(file);
        if (c == EOF || c == '\n') {
            if (firstDigit) {
                int value = 10 * (firstDigit - '0') + (lastDigit - '0');
                answer1 += value;
                firstDigit = '\0';
                lastDigit = '\0';
            }
        } else {
            if (isdigit(c)) {
                if (!firstDigit) {
                    firstDigit = c;
                }
                lastDigit = c;
            }
        }
    } while (c != EOF);

    printf("Advent of Code 2023!\n");
    printf("Day 1\n");
    printf("Part 1: %d\n", answer1);
    printf("Part 2: TODO\n");

}
