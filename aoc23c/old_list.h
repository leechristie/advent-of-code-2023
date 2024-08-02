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
} OldList;

void old_list_create(OldList *, size_t);
void old_list_destroy(OldList *);
void old_list_ensure_capacity(OldList *, int);
void old_list_append(OldList *, void *);
void old_list_get(OldList *, void *, int);
int old_list_element_equals(OldList *, int, void *);
int old_list_index_of(OldList *, void *);

#endif //AOC23C_LIST_H
