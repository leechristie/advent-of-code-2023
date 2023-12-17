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
bool is_any(char, const char *);
bool read_string_until(FILE *, char, char *, size_t);
bool read_string_until_any(FILE *, const char *, char *, size_t, char *);
bool ignore_string(FILE *, const char *);
bool ignore_char(FILE *, char);
bool _deprecated_ignore(FILE *, const char *);
int read_int(FILE *);
int read_int_checked(FILE *, int lower, int bound);
long parse_long(char * str);
int parse_int(char * str);

#endif //AOC23C_PUZZLE_H
