// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "errortools.h"

noreturn void die(const char * const error_message) {
    fprintf(stderr, "%s\n", error_message);
    exit(1);
}
