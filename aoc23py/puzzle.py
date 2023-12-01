# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from typing import Iterator

INPUT_PATH = '../input/'


def input_lines(*, day: int) -> Iterator[str]:
    with open(f'{INPUT_PATH}input{day:02}.txt') as file:
        for line in file:
            line = line.strip()
            yield line
