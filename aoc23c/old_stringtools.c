// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "old_stringtools.h"
#include "old_errortools.h"

bool old_is_any(char c, const char * characters) {
    size_t index = 0;
    while (characters[index] != '\0') {
        if (c == characters[index])
            return true;
        index++;
    }
    return false;
}

long old_parse_long(char * str) {
    size_t length = strlen(str);
    if (length < 1 || (str[0] != '-' && !isdigit(str[0])))
        old_die("unable to parse long");
    errno = 0;
    char *end;
    long rv = strtol(str, &end, 10);
    size_t read = end - str;
    if (errno || read != length)
        old_die("unable to parse long");
    return rv;
}

int old_parse_int(char * str) {
    long rv = old_parse_long(str);
    if (rv < INT_MIN || rv > INT_MAX)
        old_die("unable to parse int");
    return (int) rv;
}

char * old_lstrip_view(char * string) {
    while (*string == ' ')
        string++;
    return string;
}
