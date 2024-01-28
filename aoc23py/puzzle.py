# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from collections import deque
from typing import Iterator, TypeVar, Iterable

INPUT_PATH = '../input/'


def input_lines(*, day: int, example: bool = False) -> Iterator[str]:
    prefix = 'example' if example else 'input'
    with open(f'{INPUT_PATH}{prefix}{day:02}.txt') as file:
        for line in file:
            line = line.strip()
            yield line


def sliding_window(gen: Iterator[str], window_size: int) -> Iterator[list[str]]:
    lines: deque[str] = deque()
    for line in gen:
        lines.append(line)
        if len(lines) == window_size:
            yield list(lines)
            lines.popleft()


T = TypeVar('T')


def infinite_repeat(iterable: Iterable[T]) -> Iterator[T]:
    while True:
        yield from iterable
