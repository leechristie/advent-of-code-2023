// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdbool.h>
#include <assert.h>
#include "day04.h"
#include "puzzle.h"

#define COUNT_PICKED (10)
#define COUNT_WINNING (25)
#define BOUND (100)

static bool read_ticket(FILE *, int *, int *, int *);
static void set_lookup(const int *, bool *);
static int calc_score(const bool *, const int *);
static void unset_lookup(const int *, bool *);

void solve04(void) {

    FILE * file = open_input_file(4);

    bool lookup[BOUND] = {false};
    int answer1 = 0;

    int i = 1;
    int card_number;
    int picked[COUNT_PICKED];
    int winning[COUNT_WINNING];
    while (read_ticket(file, &card_number, picked, winning)) {
        assert(card_number == i);
        set_lookup(picked, lookup);
        answer1 += calc_score(lookup, winning);
        unset_lookup(picked, lookup); // lookup = {0};
        i++;
    }

    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 4\n");
    printf("Part 1: %d\n", answer1);
    printf("Part 2: TODO\n");

}

static bool read_ticket(FILE * file,
                        int * card_number,
                        int * picked,
                        int * winning) {

    // read the card number (or return false if EOF)
    if (!ignore(file, "Card"))
        return false;
    *card_number = read_int(file);
    assert(ignore(file, ":"));

    // read the list of picked numbers
    for (size_t i = 0; i < COUNT_PICKED; i++)
        picked[i] = read_int_checked(file, 0, BOUND);
    assert(ignore(file, "|"));

    // read the list of winning numbers
    for (size_t i = 0; i < COUNT_WINNING; i++)
        winning[i] = read_int_checked(file, 0, BOUND);

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
