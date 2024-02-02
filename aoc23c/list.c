// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdbool.h>
#include "list.h"
#include "errortools.h"

void list_create(List * list, size_t element_size) {
    if (list == NULL)
        die("cannot init NULL list");
    list->element_size = element_size;
    list->capacity = 4;
    list->length = 0;
    list->array = malloc(list->element_size * list->capacity);
    if (list->array == NULL)
        die("cannot allocate to init list");
}

void list_destroy(List * list) {
    if (list == NULL)
        die("cannot destroy NULL list");
    if (list->array != NULL)
        free(list->array);
}

void list_ensure_capacity(List * list, int new_capacity) {
    if (new_capacity >= list->capacity)
        return;
    int target_capacity = list->capacity;
    while (target_capacity < new_capacity)
        target_capacity *= 2;
    char * expanded = realloc(list->array, target_capacity);
    if (expanded == NULL)
        die("unable to expand list by realloc");
    list->array = expanded;
    list->capacity = target_capacity;
}

void list_append(List * list, void * element) {
    char * source = (char *) element;
    list_ensure_capacity(list, list->length + 1);
    char * dest = list->array + (list->element_size * list->length);
    for (size_t i = 0; i < list->element_size; i++)
        dest[i] = source[i];
    list->length++;
}

void list_get(List * list, void * element, int index) {
    char * dest = (char *) element;
    if (index < 0 || index >= list->length)
        die("invalid list index");
    char * source = list->array + (list->element_size * index);
    for (size_t i = 0; i < list->element_size; i++)
        dest[i] = source[i];
}

int list_element_equals(List * list, int index, void * element) {
    char * a = list->array + (list->element_size * index);
    char * b = (char *) element;
    for (size_t i = 0; i < list->element_size; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

int list_index_of(List * list, void * element) {
    for (int i = 0; i < list->length; i++)
        if (list_element_equals(list, i, element))
            return (int) i;
    return -1;
}
