// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdlib.h>

#include "day01.h"
#include "puzzle.h"

int main(int argc, char * argv[]) {

    if (argc < 2)
        die("Valid day not specified in command line argument.");

    const int day = atoi(argv[argc - 1]);
    switch (day) {
        case 1:
            solve01();
            break;
        default:
            die("Valid day not specified in command line argument.");
    }

    return 0;

}
