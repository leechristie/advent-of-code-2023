// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23C_PUZZLE_H
#define AOC23C_PUZZLE_H

#include <stdnoreturn.h>
#include <stdio.h>
#include <stdbool.h>

noreturn void die(char * error_message);
FILE * open_input_file(int day);
FILE * open_example_file(int day);
bool ignore(FILE *, const char *);
int read_int(FILE *);
int read_int_checked(FILE *, int lower, int bound);

#endif //AOC23C_PUZZLE_H
