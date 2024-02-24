// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdlib.h>
#include "matrix.h"
#include "errortools.h"

void dimensions_print(Dimensions dimensions) {
    printf("%zu x %zu", dimensions.width, dimensions.height);
}

void absolute_2d_print(Absolute2D point) {
    printf("(%d, %d)", point.x, point.y);
}

void relative_2d_print(Relative2D point) {
    printf("[");
    if (point.dx > 0)
        printf("+");
    printf("%d", point.dx);
    printf(", ");
    if (point.dy > 0)
        printf("+");
    printf("%d", point.dy);
    printf("]");
}

void matrix_create(Matrix * matrix, size_t element_size, Dimensions dimensions) {
    if (matrix == NULL)
        die("cannot init NULL matrix");
    matrix->element_size = element_size;
    matrix->dimensions = dimensions;
    matrix->array = malloc(element_size * dimensions.width * dimensions.height);
    if (matrix->array == NULL)
        die("cannot allocate to init matrix");
}

void matrix_set(Matrix * matrix, Absolute2D position, void * element) {
    if (position.x < 0)
        die("negative x position in set");
    if (position.y < 0)
        die("negative y position in set");
    if ((size_t) position.x >= matrix->dimensions.width)
        die("too large x position in set");
    if ((size_t) position.y >= matrix->dimensions.height)
        die("too large y position in set");
    char * source = (char *) element;
    size_t offset = (matrix->dimensions.width) * (size_t) position.y + (size_t) position.x;
    char * dest = matrix->array + (matrix->element_size * offset);
    for (size_t i = 0; i < matrix->element_size; i++)
        dest[i] = source[i];
}

void matrix_get(Matrix * matrix, Absolute2D position, void * return_address) {
    if (position.x < 0)
        die("negative x position in set");
    if (position.y < 0)
        die("negative y position in set");
    if ((size_t) position.x >= matrix->dimensions.width)
        die("too large x position in set");
    if ((size_t) position.y >= matrix->dimensions.height)
        die("too large y position in set");
    char * dest = (char *) return_address;
    size_t offset = (matrix->dimensions.width) * (size_t) position.y + (size_t) position.x;
    char * source = matrix->array + (matrix->element_size * offset);
    for (size_t i = 0; i < matrix->element_size; i++)
        dest[i] = source[i];
}

void matrix_destroy(Matrix * matrix) {
    if (matrix == NULL)
        die("cannot destroy NULL matrix");
    if (matrix->array != NULL)
        free(matrix->array);
}
