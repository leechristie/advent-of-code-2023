// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "days.h"
#include "old_puzzletools.h"
#include "old_filetools.h"
#include "old_errortools.h"
#include "old_list.h"
#include "old_mathtools.h"

typedef struct {
    char lhs[4];
    char left[4];
    char right[4];
} BodyEntry;
static bool read_body_entry(FILE *, BodyEntry *);

void solve08(void) {

    // open the input file
    FILE * file = old_open_input_file(8);

    // read the header (sequence of moves on the graph)
    char * header = old_read_line_alloc(file);
    if (header == NULL)
        old_die("unable to read header");
    int headerLength = strlen(header);

    // expected blank line
    assert(getc(file) == '\n');

    // get a list of only the LHS to enumerate the nodes
    OldList nodeNames;
    old_list_create(&nodeNames, 4);
    BodyEntry entry;
    while (read_body_entry(file, &entry))
        old_list_append(&nodeNames, &entry.lhs);

    // reset position in the file
    fseek(file, 0, SEEK_SET);

    // ignore the header and blank line
    old_ignore_string(file, header);
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
        int nodeIndex = old_list_index_of(&nodeNames, entry.lhs);
        lefts[nodeIndex] = old_list_index_of(&nodeNames, entry.left);
        rights[nodeIndex] = old_list_index_of(&nodeNames, entry.right);
    }

    // Part 1 - find the first stop for "AAA"
    int start = old_list_index_of(&nodeNames, "AAA");
    int stop = old_list_index_of(&nodeNames, "ZZZ");
    int current = start;
    long answer1 = 0;
    for (int i = 0; i < headerLength; i = (i + 1) % headerLength) {
        char direction = header[i];
        assert(direction == 'L' || direction == 'R');
        current = (direction == 'L') ?  lefts[current] : rights[current];
        answer1++;
        if (current == stop)
            break;
    }

    // Part 2 - LCM of all cycle periods
    long answer2 = 1;
    for (int startIndex = 0; startIndex < nodeNames.length; startIndex++) {
        char startName[4];
        old_list_get(&nodeNames, &startName, startIndex);
        bool isGhost = startName[2] == 'A';
        if (isGhost) {
            int ghostCurrent = startIndex;
            long ghostCycle = 0;
            for (int i = 0; i < headerLength; i = (i + 1) % headerLength) {
                char direction = header[i];
                assert(direction == 'L' || direction == 'R');
                ghostCurrent = (direction == 'L') ?  lefts[ghostCurrent] : rights[ghostCurrent];
                ghostCycle++;
                char currentName[4];
                old_list_get(&nodeNames, &currentName, ghostCurrent);
                if (currentName[2] == 'Z')
                    break;
            }
            answer2 = old_lcm(answer2, ghostCycle);
        }
    }

    // clean up
    old_list_destroy(&nodeNames);
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

    if (!old_read_n_characters(file, 3, bodyEntry->lhs))
        return false;
    old_ignore_string(file, " = (");
    if (!old_read_n_characters(file, 3, bodyEntry->left))
        return false;
    old_ignore_string(file, ", ");
    if (!old_read_n_characters(file, 3, bodyEntry->right))
        return false;
    old_ignore_string(file, ")\n");

    return true;

}
