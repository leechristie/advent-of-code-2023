// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <stdlib.h>

#include "days.h"
#include "old_stringtools.h"

int main(int argc, char * argv[]) {

    if (argc < 2) {
        fprintf(stderr, "%s\n", "Valid day not specified in command line argument.");
        exit(1);
    }

    const int day = old_parse_int(argv[argc - 1]);
    switch (day) {
        case 1:
            solve01();
            break;
        case 2:
            solve02();
            break;
        case 4:
            solve04();
            break;
        case 8:
            solve08();
            break;
        case 9:
            solve09();
        break;
        case 10:
            solve10();
        break;
        case 13:
            solve13();
        break;
        default:
            fprintf(stderr, "%s\n", "Valid day not specified in command line argument.");
            exit(1);
    }

    return 0;

}
