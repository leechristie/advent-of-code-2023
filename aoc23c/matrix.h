// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23C_MATRIX_H
#define AOC23C_MATRIX_H

#include <stddef.h>

typedef struct {
    size_t width;
    size_t height;
} Dimensions;

typedef struct {
    int x;
    int y;
} Absolute2D;

typedef struct {
    int dx;
    int dy;
} Relative2D;

void dimensions_print(Dimensions);
void absolute_2d_print(Absolute2D);
void relative_2d_print(Relative2D);

typedef struct {
    size_t element_size;
    Dimensions dimensions;
    char * array;
} Matrix;

void matrix_create(Matrix *, size_t, Dimensions);
void matrix_set(Matrix *, Absolute2D, void *);
void matrix_get(Matrix *, Absolute2D, void *);
void matrix_destroy(Matrix *);

#endif //AOC23C_MATRIX_H
