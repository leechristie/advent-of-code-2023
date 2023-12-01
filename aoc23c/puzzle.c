// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "puzzle.h"

#define INPUT_PATH ("../../input/input%02d.txt")

// remove 2 characters because "%02d" reduces form 4 to 2 characters
#define INPUT_PATH_LEN (sizeof INPUT_PATH - 2)

noreturn void die(char * error_message) {
    printf("%s\n", error_message);
    exit(1);
}

FILE * open_input_file(int day) {
    if (day < 1 || day > 25)
        die("Invalid day.");
    char filename[INPUT_PATH_LEN] = {'\0'};
    sprintf(filename, INPUT_PATH, day);
    FILE * file = fopen(filename, "r");
    if (file == NULL)
        die("Unable to open input file.");
    return file;
}
