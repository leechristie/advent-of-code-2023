// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "file_tools.h"
#include "error_tools.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static const char * const S_INPUT_PATTERN = "../../input/input%02d.txt";  // pattern for file path
static const int S_INPUT_PATTERN_LEN = strlen(S_INPUT_PATTERN) + 1;       // add 1 for ASCII NUL
static const int S_INPUT_PATH_LEN = S_INPUT_PATTERN_LEN - 2;              // "%02d" -> "01"..."25" (2 chars shorter)

FILE * open_input_file(const int day) {

    if (day < 1 || day > 25) {
        errno = INVALID_DAY;
        return NULL;
    }

    // construct filename from input pattern
    char filename[S_INPUT_PATH_LEN];
    sprintf(filename, S_INPUT_PATTERN, day);

    // open the file
    FILE * file = fopen(filename, "r");

    return file;

}
