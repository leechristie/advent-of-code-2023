// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23C_FILETOOLS_H
#define AOC23C_FILETOOLS_H

#include <stdio.h>
#include <stdbool.h>

bool old_read_n_characters(FILE *, size_t, char *);
char * old_read_line_alloc(FILE *);
bool old_read_string_until(FILE *, char, char *, size_t);
bool old_read_string_until_any(FILE *, const char *, char *, size_t, char *);
bool old_ignore_string(FILE *, const char *);
bool old_ignore_char(FILE *, char);
bool old_chars_until(FILE *, char, size_t *);

#endif //AOC23C_FILETOOLS_H
