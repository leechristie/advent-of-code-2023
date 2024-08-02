// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <assert.h>

#include "days.h"
#include "old_puzzletools.h"
#include "old_filetools.h"
#include "old_list.h"

#include <stdlib.h>
#include <string.h>

#include "old_errortools.h"

void list_of_pointers_detroy_pointers(OldList * list) {
    if (list == NULL)
        old_die("cannot destroy pointers in NULL list");
    for (int i = 0; i < list->length; i++) {
        void * pointer;
        old_list_get(list, &pointer, i);
        if (pointer == NULL)
            old_die("cannot destroy NULL pointer found in list");
        free(pointer);
    }
}

void solve13(void) {

    printf("Advent of Code 2023\n");
    printf("Day 13\n");

    FILE * file = old_open_input_file(13);

    OldList buffer;
    old_list_create(&buffer, sizeof(char *));

    char * current;
    do {

        current = old_read_line_alloc(file);

        if (current == NULL || strlen(current) == 0) {
            printf("--------------------------------------------------\n");
            list_of_pointers_detroy_pointers(&buffer);
            old_list_destroy(&buffer);
        } else {
            printf("current = \"%s\"\n", current);
            old_list_append(&buffer, current);
        }

    } while (current != NULL);

    assert(getc(file) == EOF);
    fclose(file);

    printf("Part 1: TODO\n");
    printf("Part 2: TODO\n");

}
