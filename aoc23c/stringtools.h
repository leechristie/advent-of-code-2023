// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23C_STRINGTOOLS_H
#define AOC23C_STRINGTOOLS_H

#include <stdbool.h>

long parse_long(char * str);
int parse_int(char * str);
char * lstrip_view(char *);
bool is_any(char, const char *);
void print_int_array(char *, int *, size_t);

#endif //AOC23C_STRINGTOOLS_H
