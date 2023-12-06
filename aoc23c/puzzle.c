// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "puzzle.h"

#define INPUT_PATH ("../../input/input%02d.txt")
#define EXAMPLE_PATH ("../../input/example%02d.txt")

// remove 2 characters because "%02d" reduces from 4 to 2 characters
#define INPUT_PATH_LEN (sizeof INPUT_PATH - 2)
#define EXAMPLE_PATH_LEN (sizeof EXAMPLE_PATH - 2)

noreturn void die(char * error_message) {
    fprintf(stderr, "%s\n", error_message);
    exit(1);
}

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

FILE * open_example_file(int day) {
    if (day < 1 || day > 25)
        die("Invalid day.");
    char filename[EXAMPLE_PATH_LEN];
    sprintf(filename, EXAMPLE_PATH, day);
    FILE * file = fopen(filename, "r");
    if (file == NULL)
        die("Unable to open input file.");
    return file;
}

bool ignore(FILE * file, const char * text) {
    size_t index = 0;
    while (text[index]) {
        int c = fgetc(file);
        if (c == EOF) {
            return false;
        }
        if (c == ' ' || c == '\n') {
            continue;
        }
        if (c == text[index]) {
            index++;
            continue;
        }
        die("ignore failed");
    }
    return true;
}

int read_int(FILE * file) {
    int rv;
    int success = fscanf(file, "%d", &rv);
    if (success != 1)
        die("read_int failed");
    return rv;
}

int read_int_checked(FILE * file, const int lower, const int bound) {
    int rv;
    int success = fscanf(file, "%d", &rv);
    if (success != 1)
        die("read_int_checked failed");
    if (rv < lower || rv >= bound)
        die("read_int_checked bound check failed");
    return rv;
}
