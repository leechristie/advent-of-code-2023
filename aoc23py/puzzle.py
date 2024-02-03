# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from collections import deque
from typing import *

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


def infinite_repeat(iterable: Iterable[T], enumerated: bool = False) -> Iterator[T]:
    if not enumerated:
        while True:
            yield from iterable
    else:
        while True:
            yield from enumerate(iterable)


def split(string: str, delimiter: str, dtype: Type, ctype: Type, strip: bool = False, remove_doubles: bool = False):
    assert len(delimiter) == 1
    if remove_doubles:
        while (delimiter * 2) in string:
            string = string.replace(delimiter * 2, delimiter)
    if strip:
        string = string.strip(delimiter)
    rv = [dtype(e) for e in string.split(delimiter)]
    return ctype(rv)
