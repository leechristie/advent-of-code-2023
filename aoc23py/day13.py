# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from enum import Enum
from typing import Iterator

from puzzle import input_lines


class Orientation(Enum):
    HORIZONTAL = 100
    VERTICAL = 1


MirrorChoice = tuple[Orientation, int]


class AshPattern:

    def __init__(self, height: int, width: int) -> None:
        self.data = [[False] * width for _ in range(height)]
        self.shape = height, width
        self.height = height
        self.width = width

    def __setitem__(self, key: tuple[int, int], value: bool) -> None:
        y, x = key
        self.data[y][x] = value

    def __getitem__(self, key: tuple[int, int]) -> bool:
        y, x = key
        return self.data[y][x]

    @staticmethod
    def parse(lines: list[str]) -> 'AshPattern':
        height = len(lines)
        width = len(lines[0])
        rv = AshPattern(height, width)
        for y, line in enumerate(lines):
            assert len(line) == width
            for x, char in enumerate(line):
                assert char in ('.', '#')
                rv[y, x] = char == '#'
        return rv

    @staticmethod
    def input_patterns() -> Iterator['AshPattern']:
        buffer = []
        for line in input_lines(day=13):
            line = line.strip()
            if line:
                buffer.append(line)
            else:
                yield AshPattern.parse(buffer)
                buffer.clear()
        yield AshPattern.parse(buffer)

    def horizontal_edits_required(self, y0: int) -> int:
        y1 = y0 + 1
        rv = 0
        while 0 <= y0 < self.height and 0 <= y1 < self.height:
            for x in range(self.width):
                if self[y0, x] != self[y1, x]:
                    rv += 1
            y0 -= 1
            y1 += 1
        return rv

    def vertical_edits_required(self, x0: int) -> int:
        x1 = x0 + 1
        rv = 0
        while 0 <= x0 < self.width and 0 <= x1 < self.width:
            for y in range(self.height):
                if self[y, x0] != self[y, x1]:
                    rv += 1
            x0 -= 1
            x1 += 1
        return rv

    def edits_required(self) -> dict[MirrorChoice, int]:
        rv: dict[tuple[Orientation, int], int] = {}
        for y in range(self.height - 1):
            rv[(Orientation.HORIZONTAL, y + 1)] = self.horizontal_edits_required(y)
        for x in range(self.width - 1):
            rv[(Orientation.VERTICAL, x + 1)] = self.vertical_edits_required(x)
        return rv


def solve() -> None:

    print('Advent of Code')
    print('Day 12')

    answer1 = 0
    answer2 = 0

    for pattern in AshPattern.input_patterns():
        for choice, edits_required in pattern.edits_required().items():
            orientation, offset = choice
            if edits_required == 0:
                answer1 += orientation.value * offset
            if edits_required == 1:
                answer2 += orientation.value * offset

    print(f'Part 1: {answer1}')
    print(f'Part 2: {answer2}')

    assert 34100 == answer1
    assert 33106 == answer2
