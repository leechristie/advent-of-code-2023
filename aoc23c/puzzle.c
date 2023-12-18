// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "puzzle.h"

#define INPUT_PATH ("../../input/input%02d.txt")

// remove 2 characters because "%02d" reduces from 4 to 2 characters
#define INPUT_PATH_LEN (sizeof INPUT_PATH - 2)

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

bool is_any(char c, const char * characters) {
    size_t index = 0;
    while (characters[index] != '\0') {
        if (c == characters[index])
            return true;
        index++;
    }
    return false;
}

bool read_n_characters(FILE * file, size_t n, char * buffer) {
    size_t index = 0;
    while (index < n) {
        int character = getc(file);
        if (character == EOF)
            return false;
        char c = (char) character;
        buffer[index] = c;
        index++;
    }
    buffer[index] = '\0';
    return true;
}

bool read_string_until(FILE * file, char delimiter, char * buffer, size_t max_length) {
    size_t index = 0;
    while (true) {
        int character = getc(file);
        if (character == EOF)
            return false;
        char c = (char) character;
        if (character == delimiter) {
            buffer[index] = '\0';
            return true;
        }
        if (index >= max_length) {
            buffer[index] = '\0';
            return false;
        }
        buffer[index] = c;
        index++;
    }
}

bool read_string_until_any(FILE * file, const char * delimiters, char * buffer, size_t max_length, char * found_delimiter) {
    size_t index = 0;
    while (true) {
        int character = getc(file);
        if (character == EOF)
            return false;
        char c = (char) character;
        if (is_any(c, delimiters)) {
            buffer[index] = '\0';
            *found_delimiter = c;
            return true;
        }
        if (index >= max_length) {
            buffer[index] = '\0';
            return false;
        }
        buffer[index] = c;
        index++;
    }
}

bool ignore_string(FILE * file, const char * expected) {
    size_t index = 0;
    while (expected[index]) {
        int character = getc(file);
        if (character == EOF)
            return false;
        char c = (char) character;
        if (expected[index] == c) {
            index++;
            continue;
        }
        die("ignore_string encountered wrong character");
    }
    return true;
}

bool ignore_char(FILE * file, char expected) {
    int character = getc(file);
    if (character == EOF)
        return false;
    char c = (char) character;
    if (c != expected)
        die("ignore_char encountered wrong character");
    return true;
}

bool _deprecated_ignore(FILE * file, const char * text) {
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

long parse_long(char * str) {
    size_t length = strlen(str);
    if (length < 1 || (str[0] != '-' && !isdigit(str[0])))
        die("unable to parse long");
    errno = 0;
    char *end;
    long rv = strtol(str, &end, 10);
    size_t read = end - str;
    if (errno || read != length)
        die("unable to parse long");
    return rv;
}

int parse_int(char * str) {
    long rv = parse_long(str);
    if (rv < INT_MIN || rv > INT_MAX)
        die("unable to parse int");
    return (int) rv;
}

char * lstrip_view(char * string) {
    while (*string == ' ')
        string++;
    return string;
}

void println_array(const char * name, int * array, size_t length) {
    printf("%s = [", name);
    for (size_t i = 0; i < length; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", array[i]);
    }
    printf("]\n");
}
