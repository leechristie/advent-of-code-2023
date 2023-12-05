# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

from typing import Optional

from puzzle import input_lines, sliding_window


SYMBOLS = ['*', '#', '$', '+', '/', '=', '%', '@', '&', '-']
DIGITS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']


def contains_any(haystack, needles):
    for h in haystack:
        if h in needles:
            return True
    return False


def indices_of(haystack, needles):
    rv: list[int] = []
    for i, h in enumerate(haystack):
        if h in needles:
            rv.append(i)
    return rv


def grab_number_at(line: str, index: int) -> Optional[tuple[int, int]]:
    if line[index] not in DIGITS:
        return None
    lower = index
    bound = index + 1
    while bound < len(line) and line[bound] in DIGITS:
        bound += 1
    while lower >= 1 and line[lower - 1] in DIGITS:
        lower -= 1
    return lower, int(line[lower:bound])


def solve() -> None:

    answer1 = 0
    answer2 = 0

    current_row = 1
    found: set[tuple[int, int, int]] = set()
    for above, current, below in sliding_window(input_lines(day=3), 3):
        for symbol_location in indices_of(current, SYMBOLS):
            current_symbol = current[symbol_location]
            numbers_for_current_symbol = []
            for c in [symbol_location - 1, symbol_location, symbol_location + 1]:

                col_and_value: Optional[tuple[int, int]] = grab_number_at(above, c)
                if col_and_value:
                    column, value = col_and_value
                    new_find = column, current_row - 1, value
                    if new_find not in found:
                        found.add(new_find)
                        answer1 += value
                        if current_symbol == '*':
                            numbers_for_current_symbol.append(value)

                col_and_value = grab_number_at(current, c)
                if col_and_value:
                    column, value = col_and_value
                    new_find = column, current_row, value
                    if new_find not in found:
                        found.add(new_find)
                        answer1 += value
                        if current_symbol == '*':
                            numbers_for_current_symbol.append(value)

                col_and_value = grab_number_at(below, c)
                if col_and_value:
                    column, value = col_and_value
                    new_find = column, current_row + 1, value
                    if new_find not in found:
                        found.add(new_find)
                        answer1 += value
                        if current_symbol == '*':
                            numbers_for_current_symbol.append(value)

            if len(numbers_for_current_symbol) == 2:
                answer2 += numbers_for_current_symbol[0] * numbers_for_current_symbol[1]

        current_row += 1

    print('Advent of Code 2023')
    print('Day 1')
    print(f'Part 1: {answer1}')
    assert answer1 == 550064
    print(f'Part 2: {answer2}')
    assert answer2 == 85010461
