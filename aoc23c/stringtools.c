// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "stringtools.h"
#include "errortools.h"

bool is_any(char c, const char * characters) {
    size_t index = 0;
    while (characters[index] != '\0') {
        if (c == characters[index])
            return true;
        index++;
    }
    return false;
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
