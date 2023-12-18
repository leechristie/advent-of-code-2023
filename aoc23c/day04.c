// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdbool.h>
#include <assert.h>
#include "days.h"
#include "puzzle.h"

#define COUNT_PICKED (10)
#define COUNT_WINNING (25)
#define BOUND (100)

static void set_lookup(const int *, bool *);
static int calc_score(const bool *, const int *);
static void unset_lookup(const int *, bool *);

#define MAX_WORD_SIZE (5)

static bool read_card(FILE *, int *, int *, int *);
static bool read_card_header(FILE *, char *, int *);
static bool read_single_card_number(FILE *, char *, int *);
static bool read_n_numbers(FILE *, char *, int *, int, char *);

void solve04(void) {

    FILE * file = open_input_file(4);

    bool lookup[BOUND] = {false};
    int answer1 = 0;

    int card_number;
    int picked[COUNT_PICKED];
    int winning[COUNT_WINNING];

    int i = 0;
    while (true) {

        if (!read_card(file, &card_number, picked, winning))
            break;

        printf("card_number = %d\n", card_number);
        println_array("picked", picked, COUNT_PICKED);
        println_array("winning", winning, COUNT_WINNING);
        printf("\n");

        assert(card_number == i);
        set_lookup(picked, lookup);
        answer1 += calc_score(lookup, winning);
        unset_lookup(picked, lookup); // lookup = {false};
        i++;

    }

    assert(getc(file) == EOF);
    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 4\n");
    printf("Part 1: %d\n", answer1);
    assert(24542 == answer1);
    printf("Part 2: TODO\n");

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

static int calc_score(const bool * lookup, const int * winning) {
    int rv = 0;
    for (size_t i = 0; i < COUNT_WINNING; i++)
        if (lookup[winning[i]])
            rv = rv ? rv * 2 : 1;
    return rv;
}

static void unset_lookup(const int * picked, bool * lookup) {
    for (size_t i = 0; i < COUNT_PICKED; i++)
        lookup[picked[i]] = false;
}
