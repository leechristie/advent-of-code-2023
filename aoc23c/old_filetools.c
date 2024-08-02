// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <stdbool.h>

#include "old_filetools.h"
#include "old_stringtools.h"
#include "old_errortools.h"

#define DEFAULT_STRING_CAPACITY (16)

bool old_read_n_characters(FILE * file, size_t n, char * buffer) {
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

char * old_read_line_alloc(FILE * file) {
    int capacity = DEFAULT_STRING_CAPACITY;
    char * rv = malloc(capacity);
    if (rv == NULL)
        return NULL;
    int length = 0;
    while (true) {
        int character = getc(file);
        if (character == EOF && length == 0) {
            return NULL;
        }
        if (character == EOF || character == '\n') {
            rv[length] = '\0';
            return rv;
        }
        rv[length++] = (char) character;
        if (length == capacity) {
            capacity *= 2;
            char * expanded = realloc(rv, capacity);
            if (expanded == NULL) {
                free(rv);
                return NULL;
            }
            rv = expanded;
        }
    }
}

bool old_read_string_until(FILE * file, char delimiter, char * buffer, size_t max_length) {
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

bool old_read_string_until_any(FILE * file, const char * delimiters, char * buffer, size_t max_length, char * found_delimiter) {
    size_t index = 0;
    while (true) {
        int character = getc(file);
        if (character == EOF)
            return false;
        char c = (char) character;
        if (old_is_any(c, delimiters)) {
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

bool old_ignore_string(FILE * file, const char * expected) {
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
        old_die("ignore_string encountered wrong character");
    }
    return true;
}

bool old_ignore_char(FILE * file, char expected) {
    int character = getc(file);
    if (character == EOF)
        return false;
    char c = (char) character;
    if (c != expected)
        old_die("ignore_char encountered wrong character");
    return true;
}

bool old_chars_until(FILE * file, char terminator, size_t * count) {
    *count = 0;
    while (true) {
        int character = getc(file);
        if (character == EOF)
            return false;
        if (character == terminator)
            return true;
        (*count)++;
    }
}
