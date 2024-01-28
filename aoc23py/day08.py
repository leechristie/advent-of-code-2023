# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social
from typing import Iterator
from puzzle import input_lines, infinite_repeat
import tqdm

__all__ = ['solve']


def read_header(file: Iterator[str]) -> str:
    rv = next(file)
    assert next(file) == ''  # expect blank line seperator
    return rv


def read_body(file: Iterator[str]) -> Iterator[tuple[str, tuple[str, str]]]:
    for line in file:
        lhs, line = line.replace(' ', '').split('=')
        x, y = line.strip('()').split(',')
        yield lhs, (x, y)


START = 'AAA'
END = 'ZZZ'


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 8')

    file = input_lines(day=8)
    header = read_header(file)

    body: dict[str, tuple[str, str]] = {}
    ghosts_current: list[str] = []
    for lhs, rhs in read_body(file):
        body[lhs] = rhs
        if lhs.endswith('A'):
            ghosts_current.append(lhs)

    answer1 = 0
    current = START
    for direction in infinite_repeat(header):
        assert direction in ('L', 'R')
        current = body[current][0 if direction == 'L' else 1]
        answer1 += 1
        if current == END:
            break
    print(f'Part 1: {answer1}')
    assert 12169 == answer1

    answer2 = 0
    for direction in tqdm.tqdm(infinite_repeat(header)):
        assert direction in ('L', 'R')
        for ghost_index, ghost_position in enumerate(ghosts_current):
            ghost_position = body[ghost_position][0 if direction == 'L' else 1]
            ghosts_current[ghost_index] = ghost_position
        answer2 += 1
        if all(ghost_position.endswith('Z') for ghost_position in ghosts_current):
            break
    print(f'Part 2: {answer2}')
