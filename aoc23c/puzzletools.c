// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "puzzletools.h"
#include "errortools.h"

#define INPUT_PATH ("../../input/input%02d.txt")

// remove 2 characters because "%02d" reduces from 4 to 2 characters
#define INPUT_PATH_LEN (sizeof INPUT_PATH - 2)

FILE * open_input_file(int day) {
    if (day < 1 || day > 25)
        die("Invalid day.");
    char filename[INPUT_PATH_LEN];
    sprintf(filename, INPUT_PATH, day);
    FILE * file = fopen(filename, "r");
    if (file == NULL)
        die("Unable to open input file.");
    return file;
}
