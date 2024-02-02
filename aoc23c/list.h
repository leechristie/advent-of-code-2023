// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#ifndef AOC23C_LIST_H
#define AOC23C_LIST_H

#include <stddef.h>

typedef struct {
    size_t element_size;
    int capacity;
    int length;
    char * array;
} List;

void list_create(List *, size_t);
void list_destroy(List *);
void list_ensure_capacity(List *, int);
void list_append(List *, void *);
void list_get(List *, void *, int);
int list_element_equals(List *, int, void *);
int list_index_of(List *, void *);

#endif //AOC23C_LIST_H
