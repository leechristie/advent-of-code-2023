# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from typing import Iterator

INPUT_PATH = '../input/'


def input_lines(*, day: int, example: bool = False) -> Iterator[str]:
    prefix = 'example' if example else 'input'
    with open(f'{INPUT_PATH}{prefix}{day:02}.txt') as file:
        for line in file:
            line = line.strip()
            yield line


def sliding_window(gen: Iterator[str], window_size: int) -> Iterator[str]:
    lines: tuple[str] = tuple()
    for line in gen:
        lines += (line, )
        if len(lines) == window_size:
            yield lines
            lines = lines[1:]
