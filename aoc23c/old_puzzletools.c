// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <string.h>

#include "old_puzzletools.h"
#include "old_errortools.h"

#define INPUT_PATH ("../../input/input%02d.txt")

// remove 2 characters because "%02d" reduces from 4 to 2 characters
#define INPUT_PATH_LEN (sizeof INPUT_PATH - 2)

FILE * old_open_input_file(int day) {
    if (day < 1 || day > 25)
        old_die("Invalid day.");
    char filename[INPUT_PATH_LEN];
    sprintf(filename, INPUT_PATH, day);
    FILE * file = fopen(filename, "r");
    if (file == NULL)
        old_die("Unable to open input file.");
    return file;
}


