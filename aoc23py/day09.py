# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

from puzzle import *


def _extrapolate(values: list[int], bound: int) -> None:
    seen_non_zero = False
    for i in range(0, bound-1):
        values[i] = values[i+1] - values[i]
        if values[i] != 0:
            seen_non_zero = True
    if seen_non_zero:
        _extrapolate(values, bound-1)


def extrapolate(values: list[int]) -> int:
    _extrapolate(values, len(values))
    return sum(values)


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 9')

    answer1 = 0
    answer2 = 0
    for line in input_lines(day=9):
        forwards: list[int] = split(line, ' ', ctype=list, dtype=int)
        backwards = forwards[::-1]
        answer1 += extrapolate(forwards)
        answer2 += extrapolate(backwards)

    print(f'Part 1: {answer1}')
    assert 1972648895 == answer1

    print(f'Part 2: {answer2}')
    assert 919 == answer2
