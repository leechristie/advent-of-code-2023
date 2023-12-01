# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

from puzzle import input_lines


DIGITS = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']


def strip_digit(string: str,
                include_words: bool) -> tuple[int | None, str]:
    if string[0] in '123456789':
        return int(string[0]), string[1:]
    if include_words:
        for index, digit in enumerate(DIGITS):
            if string.startswith(digit):
                return index + 1, string[1:]
    return None, string[1:]


def find_digits(string: str, include_words=False) -> list[int]:
    rv = []
    while string:
        digit, string = strip_digit(string, include_words)
        if digit is not None:
            rv.append(digit)
    return rv


def first_and_last_digits(digits: list[int]) -> int:
    return int(f'{digits[0]}{digits[-1]}')


def solve() -> None:
    answer1 = 0
    answer2 = 0
    for line in input_lines(day=1):
        answer1 += first_and_last_digits(find_digits(line))
        answer2 += first_and_last_digits(find_digits(line, include_words=True))
    print('Advent of Code 2023')
    print('Day 1')
    print(f'Part 1: {answer1}')
    print(f'Part 2: {answer2}')
