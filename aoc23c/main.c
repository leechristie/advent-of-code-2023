// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <stdlib.h>
#include "day01.h"

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("Valid day not specified in command line argument.\n");
        return 1;
    }

    const int day = atoi(argv[argc - 1]);
    switch (day) {
        case 1:
            solve01();
            break;
        default:
            printf("Valid day not specified in command line argument.\n");
            return 1;
    }

    return 0;

}
