//
// Created by Lee A. Christie on 03/08/2024.
//

#include "string_tools.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static const int S_DEFAULT_STRING_LENGTH = 16;

typedef struct {
    char * data;
    int length;
    int capacity;
} S_StringBuffer;

static void s_new_string_buffer(S_StringBuffer * string) {
    char * data = malloc(S_DEFAULT_STRING_LENGTH + 1);
    if (data != NULL) {
        data[0] = '\0';
        string->data = data;
        string->length = 0;
        string->capacity = S_DEFAULT_STRING_LENGTH;
    }
}

/**
 * @brief Doubles the capacity of the given string buffer.
 *
 * Doubles the capacity of the given string buffer. If unable to allocate, the data will be set to NULL.
 *
 * @param string the string buffer
 */
static void s_string_buffer_double_capacity(S_StringBuffer * string) {
    string->capacity *= 2;
    string->data = reallocf(string->data, string->capacity + 1);
    if (string->data == NULL) {
        string->capacity = 0;
        string->length = 0;
    }
}

static char * s_string_buffer_to_string(S_StringBuffer string) {

    if (string.data == NULL)
        return NULL;

    // if the string is too big
    if (string.capacity > string.length) {

        // shrink the pointer, or change to NULL if unable to allocate
        return reallocf(string.data, string.length + 1);

    }

    // return the data if we don't need to shrink
    return string.data;

}

char * read_line(FILE * file) {
    S_StringBuffer rv;
    s_new_string_buffer(&rv);
    if (rv.data == NULL)
        return NULL;
    while (true) {

        int character = getc(file);

        if (character == EOF) {

            // if the first character is EOF, we don't return anything
            if (rv.length == 0) {
                errno = 0;
                return NULL;
            }

            // if a character other than the first is EOF, treat like a new line
            character = '\n';

        }

        if (character == '\n') {
            return s_string_buffer_to_string(rv);
        }

        // expand the string buffer if needed
        if (rv.length == rv.capacity) {
            s_string_buffer_double_capacity(&rv);
            if (rv.data == NULL)
                return NULL;
        }

        assert(rv.capacity > rv.length);
        assert(rv.data[rv.length] == '\0');
        rv.data[rv.length] = character;
        rv.length++;
        rv.data[rv.length] = '\0';  // add NUL in the next place, which will exist due to + 1 on alloc

    }
}
