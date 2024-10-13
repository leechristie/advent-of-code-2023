# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

import numpy as np

from puzzle import input_lines

SYMBOLS = ('.', '#', 'O')

def load_grid(example: bool=False) -> np.ndarray:
    lines = list(input_lines(day=14, example=example))
    width = len(lines[0])
    height = len(lines)
    rv = np.zeros((height, width), dtype=int)
    for y, line in enumerate(lines):
        for x, character in enumerate(line):
            assert character in SYMBOLS
            rv[y, x] = SYMBOLS.index(character)
    return rv


def print_grid(grid: np.ndarray) -> None:
    for y in range(grid.shape[0]):
        for x in range(grid.shape[1]):
            print(SYMBOLS[grid[y, x]], end='')
        print()


def move_all_north(grid: np.ndarray) -> None:
    for x in range(grid.shape[1]):
        moved = True
        while moved:
            moved = False
            for y in range(1, grid.shape[0]):
                if grid[y-1, x] == 0 and grid[y, x] == 2:
                    grid[y - 1, x] = 2
                    grid[y, x] = 0
                    moved = True


def calc_row_weight(multiplier: int, grid: np.ndarray, y: int) -> int:
    rv = 0
    for x in range(grid.shape[1]):
        if grid[y, x] == 2:
            rv += multiplier
    return rv


def score_grid(grid: np.ndarray) -> int:
    multiplier = grid.shape[0]
    rv = 0
    for y in range(grid.shape[0]):
        rv += calc_row_weight(multiplier, grid, y)
        multiplier -= 1
    return rv


def solve() -> None:

    grid = load_grid(example=False)

    print('Before:')
    print_grid(grid)
    print()

    move_all_north(grid)

    print('After:')
    print_grid(grid)
    print()

    answer1 = score_grid(grid)

    print('Advent of Code 2023')
    print('Day 14')
    print(f'Part 1: {answer1}')
    print('Part 2: TODO')
