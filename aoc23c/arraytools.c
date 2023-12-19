// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "arraytools.h"

void println_array(const char * name, int * array, size_t length) {
    printf("%s = [", name);
    for (size_t i = 0; i < length; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", array[i]);
    }
    printf("]\n");
}

void left_shift_array(int * array, size_t length) {
    for (size_t i = 1; i < length; i++)
        array[i-1] = array[i];
    array[length - 1] = 0;
}
