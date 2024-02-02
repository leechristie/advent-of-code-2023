// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdlib.h>
#include <assert.h>
#include "days.h"
#include "puzzletools.h"
#include "filetools.h"
#include "errortools.h"
#include "list.h"

typedef struct {
    char lhs[4];
    char left[4];
    char right[4];
} BodyEntry;
static bool read_body_entry(FILE *, BodyEntry *);

void solve08(void) {

    // open the input file
    FILE * file = open_input_file(8);

    // read the header (sequence of moves on the graph)
    char * header = read_line_alloc(file);
    if (header == NULL)
        die("unable to read header");
    printf("header = \"%s\"\n", header);

    // expected blank line
    assert(getc(file) == '\n');

    // get a list of only the LHS to enumerate the nodes
    List nodeNames;
    list_create(&nodeNames, 4);
    BodyEntry entry;
    while (read_body_entry(file, &entry))
        list_append(&nodeNames, &entry.lhs);

    // reopen the file
    assert(getc(file) == EOF);
    fclose(file);
    file = open_input_file(8);

    // print out the list of nodes
    printf("nodeNames = {");
    for (int i = 0; i < nodeNames.length; i++) {
        if (i != 0)
            printf(", ");
        char lhs[4];
        list_get(&nodeNames, &lhs, i);
        printf("%s", lhs);
    }
    printf("}\n");

    // ignore the header and blank line
    ignore_string(file, header);
    assert(getc(file) == '\n'); // line break in header line
    assert(getc(file) == '\n'); // blank line

    // read the body again, converting to ints and getting the left and right arrays
    int * lefts = malloc(sizeof(int) * nodeNames.length);
    int * rights = malloc(sizeof(int) * nodeNames.length);
    for (int i = 0; i < nodeNames.length; i++) {
        lefts[i] = -1;
        rights[i] = -1;
    }
    while (read_body_entry(file, &entry)) {
        int nodeIndex = list_index_of(&nodeNames, entry.lhs);
        lefts[nodeIndex] = list_index_of(&nodeNames, entry.left);
        rights[nodeIndex] = list_index_of(&nodeNames, entry.right);
    }

    // print out the left and right lists
    printf("lefts = {");
    for (int i = 0; i < nodeNames.length; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", lefts[i]);
        if (lefts[i] < 0)
            die("missing left index");
    }
    printf("}\n");
    printf("rights = {");
    for (int i = 0; i < nodeNames.length; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", rights[i]);
        if (lefts[i] < 0)
            die("missing right index");
    }
    printf("}\n");

    long answer1 = 0;
    long answer2 = 0;

    // clean up
    list_destroy(&nodeNames);
    free(lefts);
    free(rights);
    free(header);
    assert(getc(file) == EOF);
    fclose(file);

    // output answers
    printf("Advent of Code 2023!\n");
    printf("Day 8\n");
    printf("Part 1: %ld\n", answer1);
    printf("Part 2: %ld\n", answer2);

    // check answers
    assert(12169 == answer1);
    assert(12030780859469 == answer2);

}

static bool read_body_entry(FILE * file, BodyEntry * bodyEntry) {

    if (!read_n_characters(file, 3, bodyEntry->lhs))
        return false;
    ignore_string(file, " = (");
    if (!read_n_characters(file, 3, bodyEntry->left))
        return false;
    ignore_string(file, ", ");
    if (!read_n_characters(file, 3, bodyEntry->right))
        return false;
    ignore_string(file, ")\n");

    return true;

}
