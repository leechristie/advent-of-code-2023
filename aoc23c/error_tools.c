// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "error_tools.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INVALID_DAY = 1000;

const char * custom_error_message(const int code) {
    switch (code) {
        case INVALID_DAY:
            return "Invalid Advent of Code day number";
        default:
            return strerror(code);
    }
}

void exit_if_errno_set(const char * const message) {
    if (errno != 0) {
        fprintf(stderr, "%s\n: %s\n", message, custom_error_message(errno));
        exit(errno);
    }
}
