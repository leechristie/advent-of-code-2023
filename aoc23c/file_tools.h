// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef FILE_TOOLS_H
#define FILE_TOOLS_H

#include <stdio.h>

/**
 * @brief Opens the Advent of Code input text file from the input file directory.
 *
 * @param day The Advent of Code day, 1 to 25.
 * @return The file handle or NULL if the file could not be opened.
 * @exception INVALID_DAY if the day is not 1 to 25
 * @exception ENOENT if the input file is not found
 */
FILE * open_input_file(int day);

#endif //FILE_TOOLS_H
