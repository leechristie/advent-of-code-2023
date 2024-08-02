// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "old_arraytools.h"

void old_println_array(const char * name, int * array, size_t length) {
    printf("%s = [", name);
    for (size_t i = 0; i < length; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", array[i]);
    }
    printf("]\n");
}

void old_left_shift_array(int * array, size_t length) {
    for (size_t i = 1; i < length; i++)
        array[i-1] = array[i];
    array[length - 1] = 0;
}

int old_sum_int_array(int * array, size_t length) {
    int rv = 0;
    for (size_t i = 0; i < length; i++)
        rv += array[i];
    return rv;
}

void old_copy_int_array_backwards(const int * from, int * to, size_t length) {
    size_t i = 0;
    size_t j = length - 1;
    while (i < length)
        to[j--] = from[i++];
}
