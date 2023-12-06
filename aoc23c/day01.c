// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "puzzle.h"
#include "day01.h"

struct tagDigits {
    char firstStandard;
    char lastStandard;
    char first;
    char last;
};
typedef struct tagDigits Digits;

static int parse_two_digits(int, int);
static void update_digits(int, Digits *, size_t *);
static void complete_current_line(Digits *, unsigned int *, unsigned int *, size_t *);

#define MAX_DIGIT_LENGTH (5)
#define NUM_DIGITS (10)
static const char DIGITS_ENGLISH[NUM_DIGITS][MAX_DIGIT_LENGTH + 1] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
};

void solve01(void) {

    FILE * file = open_input_file(1);

    size_t digitPositions[NUM_DIGITS] = {0};

    unsigned int answer1 = 0;
    unsigned int answer2 = 0;

    Digits digit;
    digit.firstStandard = '\0';
    digit.lastStandard = '\0';
    digit.first = '\0';
    digit.last = '\0';

    int c;
    do {
        c = fgetc(file);
        if (c == '\n')
            complete_current_line(&digit, &answer1, &answer2, digitPositions);
        else if (c != EOF)
            update_digits(c, &digit, digitPositions);
    } while ((char) c != EOF);

    assert(!digit.firstStandard && !digit.lastStandard);
    assert(!digit.first && !digit.last);

    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 1\n");
    printf("Part 1: %d\n", answer1);
    printf("Part 2: %d\n", answer2);

}

static int parse_two_digits(int firstDigit,
                            int lastDigit) {
    return 10 * (firstDigit - '0') + (lastDigit - '0');
}

static void update_digits(int c,
                          Digits * digits,
                          size_t * digitPositions) {
    if (isdigit(c)) {
        digits->lastStandard = (char) c;
        digits->last = (char) c;
        if (!digits->firstStandard)
            digits->firstStandard = (char) c;
        if (!digits->first)
            digits->first = (char) c;
        for (size_t d = 0; d < NUM_DIGITS; d++) {
            if (digitPositions[d])
                digitPositions[d] = 0;
        }
    } else {
        for (size_t d = 0; d < NUM_DIGITS; d++) {
            if (c == DIGITS_ENGLISH[d][digitPositions[d]])
                digitPositions[d]++;
            else {
                if (digitPositions[d])
                    digitPositions[d] = 0;
                if (c == DIGITS_ENGLISH[d][digitPositions[d]])
                    digitPositions[d]++;
            }
            if (DIGITS_ENGLISH[d][digitPositions[d]] == '\0') {
                digits->last = '0' + (char) d;
                if (!digits->first)
                    digits->first = '0' + (char) d;
                digitPositions[d] = 0;
            }
            assert(digitPositions[d] < MAX_DIGIT_LENGTH + 1);
        }
    }
}

static void complete_current_line(Digits * digits,
                                  unsigned int * answer1,
                                  unsigned int * answer2,
                                  size_t * digitPositions) {
    if (digits->firstStandard) {
        assert(digits->lastStandard);
        int num = parse_two_digits(digits->firstStandard,
                                   digits->lastStandard);
        *answer1 += num;
        digits->firstStandard = '\0';
        digits->lastStandard = '\0';
    }
    if (digits->first) {
        assert(digits->last);
        int num = parse_two_digits(digits->first,
                                   digits->last);
        *answer2 += num;
        digits->first = '\0';
        digits->last = '\0';
    }
    for (size_t d = 0; d < NUM_DIGITS; d++)
        if (digitPositions[d])
            digitPositions[d] = 0;
}
