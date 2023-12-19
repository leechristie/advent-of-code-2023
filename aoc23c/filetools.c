// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <stdbool.h>

#include "filetools.h"
#include "stringtools.h"
#include "errortools.h"

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
