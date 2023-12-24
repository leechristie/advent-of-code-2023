# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

from collections import deque
from typing import Optional

from puzzle import input_lines, sliding_window


SYMBOLS = ['*', '#', '$', '+', '/', '=', '%', '@', '&', '-']
DIGITS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']


def contains_any(haystack: str, needles: list[str]) -> bool:
    for h in haystack:
        if h in needles:
            return True
    return False


def indices_of(haystack: str, needles: list[str]) -> list[int]:
    rv: list[int] = []
    for i, h in enumerate(haystack):
        if h in needles:
            rv.append(i)
    return rv


def grab_number_at(line: str, index: int) -> Optional[tuple[int, int]]:

    # ignore if not a digit
    if line[index] not in DIGITS:
        return None

    # find the last digit
    bound = index + 1
    while bound < len(line) and line[bound] in DIGITS:
        bound += 1

    # find the first digit
    lower = index
    while lower >= 1 and line[lower - 1] in DIGITS:
        lower -= 1

    # return the location and value of the number
    return lower, int(line[lower:bound])


def look_for_number(line: str,
                    column: int,
                    found: set[int],
                    part_numbers: Optional[list[int]],
                    answers: list[int]):

    # if the location is a part of a number
    col_and_value: Optional[tuple[int, int]] = grab_number_at(line, column)
    if col_and_value:
        column, value = col_and_value

        # if the number has not yet been seen
        if column not in found:
            found.add(column)

            # Part 1: the sum of all the numbers adjacent to symbols
            answers[0] += value

            # Part 2: the sum of products of two numbers around '*'
            if part_numbers is not None:
                part_numbers.append(value)
                if len(part_numbers) == 2:
                    answers[1] += part_numbers[0] * part_numbers[1]


def solve() -> None:

    answers = [0, 0]

    found_sets: deque[set[int]] = deque([set(), set(), set()])
    for window in sliding_window(input_lines(day=3), 3):

        # the current line is the middle of the sliding window
        current = window[1]
        for symbol_location in indices_of(current, SYMBOLS):

            # part_numbers is only used if the symbol is '*' indicating a gear
            part_numbers: Optional[list[int]] = [] \
                if current[symbol_location] == '*' else None

            # look in the 9 positions around the symbol
            for column in [symbol_location - 1, symbol_location, symbol_location + 1]:
                for line, found in zip(window, found_sets):

                    # check for numbers in those positions
                    look_for_number(line, column,                 # in arguments
                                    found, part_numbers, answers  # out arguments
                                    )

        # no longer need to track the found set of the above line
        found_sets.popleft()

        # need new set to track the next line below
        found_sets.append(set())

    print('Advent of Code 2023')
    print('Day 1')
    print(f'Part 1: {answers[0]}')
    print(f'Part 2: {answers[1]}')
    assert 550064 == answers[0]
    assert 85010461 == answers[1]
