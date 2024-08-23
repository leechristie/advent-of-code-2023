// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "days.h"
#include "error_tools.h"
#include "file_tools.h"
#include "string_tools.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void solve01(void) {

    printf("Advent of Code 2023!\n");
    printf("Day 1\n");

    // open the Advent of Code input file
    FILE * const file = open_input_file(1);
    exit_if_errno_set("Unable to open Advent of Code input file");
    assert(file != NULL);

    // loop over lines of the file
    char * line;
    while ((line = read_line(file)) != NULL) {
        exit_if_errno_set("Unable to read line");

        printf("%s\n", line);

        free(line);
    }

    // close the file
    fclose(file);

    printf("Part 1: TODO\n");
    printf("Part 2: TODO\n");

}

//
// #include <stdio.h>
// #include <ctype.h>
// #include <assert.h>
//
// #include "old_puzzletools.h"
//
// typedef struct {
//     char first;
//     char last;
// } Digits;
//
// static void reset_digit_positions(size_t *);
// static int parse_digits(Digits *);
// static void update_digits(int, Digits *, Digits *, size_t *);
// static void complete_current_line(Digits *, Digits *, unsigned int *, unsigned int *, size_t *);
//
// #define MAX_DIGIT_LENGTH (5)
// #define NUM_DIGITS (10)
// static const char DIGITS_ENGLISH[NUM_DIGITS][MAX_DIGIT_LENGTH + 1] = {
//         "zero",
//         "one",
//         "two",
//         "three",
//         "four",
//         "five",
//         "six",
//         "seven",
//         "eight",
//         "nine"
// };
//
// void solve01(void) {
//
//     FILE * file = old_open_input_file(1);
//
//     size_t digitPositions[NUM_DIGITS] = {0};
//
//     unsigned int answer1 = 0;
//     unsigned int answer2 = 0;
//
//     Digits standardDigits = {'\0', '\0'};
//     Digits digits = {'\0', '\0'};
//
//     int c;
//     do {
//         c = fgetc(file);
//         if (c == '\n')
//             complete_current_line(&standardDigits, &digits, &answer1, &answer2, digitPositions);
//         else if (c != EOF)
//             update_digits(c, &standardDigits, &digits, digitPositions);
//     } while (c != EOF);
//
//     assert(!standardDigits.first && !standardDigits.last);
//     assert(!digits.first && !digits.last);
//
//     fclose(file);
//
//     printf("Advent of Code 2023!\n");
//     printf("Day 1\n");
//     printf("Part 1: %d\n", answer1);
//     printf("Part 2: %d\n", answer2);
//
//     assert(54708 == answer1);
//     assert(54087 == answer2);
//
// }
//
// static int parse_digits(Digits * digits) {
//     assert(digits->first && digits->last);
//     return 10 * (digits->first - '0') + (digits->last - '0');
// }
//
// static void reset_digit_positions(size_t * digitPositions) {
//     for (size_t d = 0; d < NUM_DIGITS; d++)
//         digitPositions[d] = 0;
// }
//
// static void update_digits(int c,
//                           Digits * standardDigits,
//                           Digits * digits,
//                           size_t * digitPositions) {
//
//     if (isdigit(c)) {
//
//         standardDigits->last = (char) c;
//         digits->last = (char) c;
//         if (!standardDigits->first)
//             standardDigits->first = (char) c;
//         if (!digits->first)
//             digits->first = (char) c;
//
//         reset_digit_positions(digitPositions);
//
//     } else {
//
//         for (size_t d = 0; d < NUM_DIGITS; d++) {
//
//             // advanced one character in an English digit
//             if (c == DIGITS_ENGLISH[d][digitPositions[d]])
//                 digitPositions[d]++;
//
//             // reset to start of an English digit
//             else {
//
//                 digitPositions[d] = 0;
//
//                 // remember to recheck the first if reset the digit e.g. "ttwo"
//                 if (c == DIGITS_ENGLISH[d][digitPositions[d]])
//                     digitPositions[d]++;
//
//             }
//
//             // found an English digit
//             if (DIGITS_ENGLISH[d][digitPositions[d]] == '\0') {
//                 digits->last = (char) (('0' + d) & 0x7f);
//                 if (!digits->first)
//                     digits->first = (char) (('0' + d) & 0x7f);
//                 digitPositions[d] = 0;
//             }
//
//             assert(digitPositions[d] < MAX_DIGIT_LENGTH + 1);
//
//         }
//
//     }
//
// }
//
// static void complete_current_line(Digits * standardDigits,
//                                   Digits * digits,
//                                   unsigned int * answer1,
//                                   unsigned int * answer2,
//                                   size_t * digitPositions) {
//
//     if (standardDigits->first) {
//         *answer1 += parse_digits(standardDigits);
//         standardDigits->first = '\0';
//         standardDigits->last = '\0';
//     }
//
//     if (digits->first) {
//         *answer2 += parse_digits(digits);
//         digits->first = '\0';
//         digits->last = '\0';
//     }
//
//     reset_digit_positions(digitPositions);
//
// }
