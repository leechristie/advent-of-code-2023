// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23C_MATRIX_H
#define AOC23C_MATRIX_H

#include <stddef.h>

typedef struct {
    size_t width;
    size_t height;
} OldDimensions;

typedef struct {
    int x;
    int y;
} OldAbsolute2D;

typedef struct {
    int dx;
    int dy;
} OldRelative2D;

void old_dimensions_print(OldDimensions);
void old_absolute_2d_print(OldAbsolute2D);
void old_relative_2d_print(OldRelative2D);

typedef struct {
    size_t element_size;
    OldDimensions dimensions;
    char * array;
} OldMatrix;

void old_matrix_create(OldMatrix *, size_t, OldDimensions);
void old_matrix_set(OldMatrix *, OldAbsolute2D, void *);
void old_matrix_get(OldMatrix *, OldAbsolute2D, void *);
void old_matrix_destroy(OldMatrix *);

#endif //AOC23C_MATRIX_H
