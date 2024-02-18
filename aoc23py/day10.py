# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from puzzle import *


class Pipe:

    def __init__(self, symbol: str, position: Absolute2D) -> None:
        assert symbol in ('F', '7', 'J', 'L', '-', '|', '.', 'S')
        self.symbol = symbol
        self.position = position

    def __repr__(self) -> str:
        return str(self)

    def __str__(self) -> str:
        return self.symbol

    def relative_connections(self) -> list[Relative2D]:
        if self.symbol == 'F':
            return [Relative2D.RIGHT, Relative2D.DOWN]
        if self.symbol == '7':
            return [Relative2D.LEFT, Relative2D.DOWN]
        if self.symbol == 'J':
            return [Relative2D.LEFT, Relative2D.UP]
        if self.symbol == 'L':
            return [Relative2D.RIGHT, Relative2D.UP]
        if self.symbol == '|':
            return [Relative2D.UP, Relative2D.DOWN]
        if self.symbol == '-':
            return [Relative2D.LEFT, Relative2D.RIGHT]
        if self.symbol == '.':
            return []
        assert self.symbol == 'S'
        raise ValueError('Cannot connect S!')

    def absolute_connections(self) -> list[Absolute2D]:
        return [self.position + relative for relative in self.relative_connections()]


class PipeMap:

    __slots__ = ['rows', 'width', 'height', 'start']

    def __init__(self, lines: Iterable[str]) -> None:
        self.rows: list[list[Pipe]] = []
        start: Optional[Absolute2D] = None
        width: Optional[int] = None
        for y, line in enumerate(lines):
            row = []
            for x, symbol in enumerate(line):
                position = Absolute2D(x=x, y=y)
                if symbol == 'S':
                    assert start is None
                    start = position
                row.append(Pipe(symbol, position))
            self.rows.append(row)
            if width is not None:
                assert width == len(row)
            else:
                width = len(row)
        assert start is not None
        self.start: Absolute2D = start
        self.height: int = len(self.rows)
        assert width is not None
        self.width: int = width
        connected_neighbors = []
        for neighbor in self.start.neighbors():
            for connection in self[neighbor].absolute_connections():
                if connection == self.start:
                    connected_neighbors.append(neighbor)
        assert len(connected_neighbors) == 2
        connected_relative = {other - self.start for other in connected_neighbors}
        start_symbol: Optional[str] = None
        for possible_pipes in ['F', '7', 'J', 'L', '|', '-']:
            if connected_relative == set(Pipe(possible_pipes, Absolute2D(x=0, y=0)).relative_connections()):
                start_symbol = possible_pipes
        assert start_symbol is not None
        self.rows[start.y][start.x] = Pipe(start_symbol, self.start)

    def __repr__(self) -> str:
        return str(self)

    def __str__(self) -> str:
        rv = f'Start: ' + repr(self.start)
        for y in range(self.height):
            line = ''
            for x in range(self.width):
                line += str(self[Absolute2D(x=x, y=y)])
            rv += '\n' + line
        return rv

    def __getitem__(self, item: Absolute2D) -> Pipe:
        if item.y < 0 or item.y >= self.height:
            return Pipe('.', item)
        if item.x < 0 or item.x >= self.width:
            return Pipe('.', item)
        return self.rows[item.y][item.x]


def solve() -> None:

    # pipe_map = PipeMap(input_lines(day=10))

    pipe_map = PipeMap(['7-F7-', '.FJ|7', 'SJLL7', '|F--J', 'LJ.LJ'])
    print(pipe_map)

    print('Advent of Code 2023')
    print('Day 10')
    print('Part 1: TODO')
    print('Part 2: TODO')
