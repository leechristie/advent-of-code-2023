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


class Absolute2D:

    def __init__(self, *, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def __repr__(self) -> str:
        return f'Absolute2D(x={self.x}, y={self.y})'

    def __str__(self) -> str:
        return f'({self.x}, {self.y})'

    def __eq__(self, other: 'Absolute2D') -> bool:
        return isinstance(other, Absolute2D) and self.x == other.x and self.y == other.y

    def neighbors(self) -> list['Absolute2D']:
        pass

    def __sub__(self, other: 'Absolute2D') -> 'Relative2D':
        return Relative2D(dx=self.x - other.x, dy=self.y - other.y)

    def __hash__(self):
        return hash((self.x, self.y))


class Relative2D:

    def __init__(self, *, dx: int, dy: int) -> None:
        self.dx = dx
        self.dy = dy

    def __repr__(self) -> str:
        return f'Relative2D(dx={self.dx}, dy={self.dy})'

    def __str__(self) -> str:
        return f'({self.dx}, {self.dy})'

    @overload
    def __add__(self, other: Absolute2D) -> Absolute2D:
        ...

    @overload
    def __add__(self, other: 'Relative2D') -> 'Relative2D':
        ...

    def __add__(self, other):
        if isinstance(other, Relative2D):
            return Relative2D(dx=self.dx+other.dx, dy=self.dy+other.dy)
        elif isinstance(other, Absolute2D):
            return Absolute2D(x=self.dx+other.x, y=self.dy+other.y)
        else:
            raise TypeError

    @overload
    def __radd__(self, other: Absolute2D) -> Absolute2D:
        ...

    @overload
    def __radd__(self, other: 'Relative2D') -> 'Relative2D':
        ...

    def __radd__(self, other):
        if isinstance(other, Relative2D):
            return Relative2D(dx=self.dx+other.dx, dy=self.dy+other.dy)
        elif isinstance(other, Absolute2D):
            return Absolute2D(x=self.dx+other.x, y=self.dy+other.y)
        else:
            raise TypeError

    def __eq__(self, other: 'Relative2D') -> bool:
        return isinstance(other, Relative2D) and self.dx == other.dx and self.dy == other.dy

    def __hash__(self):
        return hash((self.dx, self.dy))

    UP: 'Relative2D'
    DOWN: 'Relative2D'
    LEFT: 'Relative2D'
    RIGHT: 'Relative2D'


Relative2D.UP = Relative2D(dx=0, dy=-1)
Relative2D.DOWN = Relative2D(dx=0, dy=1)
Relative2D.LEFT = Relative2D(dx=-1, dy=0)
Relative2D.RIGHT = Relative2D(dx=1, dy=0)


Absolute2D.neighbors = lambda self: [self + Relative2D.UP,
                                     self + Relative2D.DOWN,
                                     self + Relative2D.LEFT,
                                     self + Relative2D.RIGHT]
