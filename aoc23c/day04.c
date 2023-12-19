// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdbool.h>
#include <assert.h>
#include "days.h"
#include "puzzletools.h"
#include "arraytools.h"
#include "filetools.h"
#include "stringtools.h"

#define COUNT_PICKED (10)
#define COUNT_WINNING (25)
#define BOUND (100)

static void set_lookup(const int *, bool *);
static int calc_score(int);
static int calc_num_matches(const bool *, const int *);
static void unset_lookup(const int *, bool *);

// max parsing buffer is length 3 string for 2-digit number with leading space
#define MAX_WORD_SIZE (3)

static bool read_card(FILE *, int *, int *, int *);
static bool read_card_header(FILE *, char *, int *);
static bool read_single_card_number(FILE *, char *, int *);
static bool read_n_numbers(FILE *, char *, int *, int, char *);

void solve04(void) {

    FILE * file = open_input_file(4);

    bool lookup[BOUND] = {false};
    int total_score = 0;

    int card_number;
    int picked[COUNT_PICKED];
    int winning[COUNT_WINNING];

    int extra_copies[COUNT_PICKED] = {0};
    long total_scratched = 0;

    while (true) {

        if (!read_card(file, &card_number, picked, winning))
            break;

        int num_copies = 1 + extra_copies[0];
        total_scratched += num_copies;
        assert(total_scratched > 0);
        left_shift_array(extra_copies, COUNT_PICKED);

        set_lookup(picked, lookup);
        int num_matches = calc_num_matches(lookup, winning);
        total_score += calc_score(num_matches);
        unset_lookup(picked, lookup); // lookup = {false}

        if (num_matches > 0) {
            for (int i = 0; i < num_matches; i++) {
                extra_copies[i] += num_copies;
                assert(extra_copies[i] > 0);
            }
        }

    }

    assert(getc(file) == EOF);
    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 4\n");
    printf("Part 1: %d\n", total_score);
    printf("Part 2: %ld\n", total_scratched);
    
    assert(24542 == total_score);
    assert(8736438 == total_scratched);

}

static bool read_card(FILE * file, int * card_number, int * picked, int * winning) {
    char buffer[MAX_WORD_SIZE + 1];
    return read_card_header(file, buffer, card_number)
           && read_n_numbers(file, buffer, picked, COUNT_PICKED, " |")
           && read_n_numbers(file, buffer, winning, COUNT_WINNING, "\n");
}

static bool read_card_header(FILE * file, char * buffer, int * rv) {
    ignore_string(file, "Card ");
    if (!read_string_until(file, ':', buffer, MAX_WORD_SIZE))
        return false;
    *rv = parse_int(lstrip_view(buffer));
    return true;
}

static bool read_n_numbers(FILE * file, char * buffer, int * rv, int count, char * terminator) {
    int chosen_number;
    for (int i = 0; i < count; i++) {
        if (!read_single_card_number(file, buffer, &chosen_number))
            return false;
        rv[i] = chosen_number;
    }
    ignore_string(file, terminator);
    return true;
}

static bool read_single_card_number(FILE * file, char * buffer, int * rv) {
    if (!read_n_characters(file, 3, buffer))
        return false;
    *rv = parse_int(lstrip_view(buffer));
    return true;
}

static void set_lookup(const int * picked, bool * lookup) {
    for (size_t i = 0; i < COUNT_PICKED; i++)
        lookup[picked[i]] = true;
}

static int calc_score(const int num_matches) {
    int rv = 0;
    for (int i = 0; i < num_matches; i++)
        rv = rv ? rv * 2 : 1;
    return rv;
}

static int calc_num_matches(const bool * lookup, const int * winning) {
    int rv = 0;
    for (size_t i = 0; i < COUNT_WINNING; i++)
        if (lookup[winning[i]])
            rv++;
    return rv;
}

static void unset_lookup(const int * picked, bool * lookup) {
    for (size_t i = 0; i < COUNT_PICKED; i++)
        lookup[picked[i]] = false;
}
