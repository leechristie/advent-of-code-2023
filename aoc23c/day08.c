// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdlib.h>
#include <assert.h>
#include "days.h"
#include "puzzletools.h"
#include "filetools.h"
#include "errortools.h"

void solve08(void) {

    FILE * file = open_input_file(8);

    // read the header (sequence of moves on the graph)
    char * header = read_line_alloc(file);
    if (header == NULL)
        die("unable to read header");
    printf("header = \"%s\"\n", header);

    // expected blank line
    assert(getc(file) == '\n');

    long answer1 = 0;
    long answer2 = 0;

    free(header);
    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 8\n");
    printf("Part 1: %ld\n", answer1);
    printf("Part 2: %ld\n", answer2);

    assert(12169 == answer1);
    assert(12030780859469 == answer2);

}
