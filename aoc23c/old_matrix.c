// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdlib.h>
#include "old_matrix.h"
#include "old_errortools.h"

void old_dimensions_print(OldDimensions dimensions) {
    printf("%zu x %zu", dimensions.width, dimensions.height);
}

void old_absolute_2d_print(OldAbsolute2D point) {
    printf("(%d, %d)", point.x, point.y);
}

void old_relative_2d_print(OldRelative2D point) {
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

void old_matrix_create(OldMatrix * matrix, size_t element_size, OldDimensions dimensions) {
    if (matrix == NULL)
        old_die("cannot init NULL matrix");
    matrix->element_size = element_size;
    matrix->dimensions = dimensions;
    matrix->array = malloc(element_size * dimensions.width * dimensions.height);
    if (matrix->array == NULL)
        old_die("cannot allocate to init matrix");
}

void old_matrix_set(OldMatrix * matrix, OldAbsolute2D position, void * element) {
    if (position.x < 0)
        old_die("negative x position in set");
    if (position.y < 0)
        old_die("negative y position in set");
    if ((size_t) position.x >= matrix->dimensions.width)
        old_die("too large x position in set");
    if ((size_t) position.y >= matrix->dimensions.height)
        old_die("too large y position in set");
    char * source = (char *) element;
    size_t offset = (matrix->dimensions.width) * (size_t) position.y + (size_t) position.x;
    char * dest = matrix->array + (matrix->element_size * offset);
    for (size_t i = 0; i < matrix->element_size; i++)
        dest[i] = source[i];
}

void old_matrix_get(OldMatrix * matrix, OldAbsolute2D position, void * return_address) {
    if (position.x < 0)
        old_die("negative x position in set");
    if (position.y < 0)
        old_die("negative y position in set");
    if ((size_t) position.x >= matrix->dimensions.width)
        old_die("too large x position in set");
    if ((size_t) position.y >= matrix->dimensions.height)
        old_die("too large y position in set");
    char * dest = (char *) return_address;
    size_t offset = (matrix->dimensions.width) * (size_t) position.y + (size_t) position.x;
    char * source = matrix->array + (matrix->element_size * offset);
    for (size_t i = 0; i < matrix->element_size; i++)
        dest[i] = source[i];
}

void old_matrix_destroy(OldMatrix * matrix) {
    if (matrix == NULL)
        old_die("cannot destroy NULL matrix");
    if (matrix->array != NULL)
        free(matrix->array);
}
