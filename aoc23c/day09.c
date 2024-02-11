// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <assert.h>

#include "days.h"
#include "puzzletools.h"
#include "filetools.h"
#include "stringtools.h"
#include "arraytools.h"

#define NUMBER_OF_VALUES (21)
#define BUFFER_SIZE (10)

static void extrapolate_pass(int *, size_t);
static int extrapolate(int *, size_t);

void solve09(void) {

    printf("Advent of Code 2023\n");
    printf("Day 9\n");

    long answer1 = 0;
    long answer2 = 0;
    int forwards[NUMBER_OF_VALUES];
    int backwards[NUMBER_OF_VALUES];
    char buffer[BUFFER_SIZE];
    char found_delimiter = '\0';
    size_t index = 0;

    FILE * file = open_input_file(9);
    while (read_string_until_any(file, " \n", buffer, BUFFER_SIZE - 1, &found_delimiter)) {

        // read the current string buffer as an integer
        int number = parse_int(buffer);

        // check there aren't more values than expected, and store the value
        assert(index < NUMBER_OF_VALUES);
        forwards[index++] = number;

        // end of list of values triggers the extrapolation calculation
        if (found_delimiter == '\n') {

            // checking we have the exact number of expected values
            assert(index == NUMBER_OF_VALUES);
            index = 0;

            // copy the values backwards for Part 2
            copy_int_array_backwards(forwards, backwards, NUMBER_OF_VALUES);

            // extrapolate based on the array of exactly NUMBER_OF_VALUES values
            answer1 += extrapolate(forwards, NUMBER_OF_VALUES);
            answer2 += extrapolate(backwards, NUMBER_OF_VALUES);

        }

    }
    assert(getc(file) == EOF);  // if the BUFFER_SIZE were too small, we would exit the loop too early
    fclose(file);

    printf("Part 1: %ld\n", answer1);
    assert(1972648895 == answer1);

    printf("Part 2: %ld\n", answer2);
    assert(919 == answer2);

}

static void extrapolate_pass(int * values, size_t bound) {
    bool non_zero_difference_seen = false;
    for (size_t i = 0; i <= bound - 2; i++) {
        values[i] = values[i + 1] - values[i];
        if (values[i] != 0)
            non_zero_difference_seen = true;
    }
    if (non_zero_difference_seen)
        extrapolate_pass(values, bound - 1);
}

static int extrapolate(int * values, size_t length) {
    extrapolate_pass(values, length);
    int extrapolated = sum_int_array(values, length);
    return extrapolated;
}
