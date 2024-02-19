# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from puzzle import *


class Pipe:

    def __init__(self, symbol: str, position: Absolute2D, pipes: Optional['PipeMap'] = None) -> None:
        assert symbol in ('F', '7', 'J', 'L', '-', '|', '.', 'S')
        self.symbol = symbol
        self.position = position
        self.pipes = pipes

    def __repr__(self) -> str:
        return f'Pipe({self.symbol}, {self.position})'

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

    def connected_pipes(self) -> list['Pipe']:
        assert self.pipes is not None
        return [self.pipes[position] for position in self.absolute_connections()]

    def __hash__(self):
        return hash(self.position)


class PipeMap:

    __slots__ = ['rows', 'width', 'height', 'start']

    def __init__(self, lines: Iterable[str]) -> None:
        self.rows: list[list[Pipe]] = []
        start_position: Optional[Absolute2D] = None
        width: Optional[int] = None
        for y, line in enumerate(lines):
            row = []
            for x, symbol in enumerate(line):
                position = Absolute2D(x=x, y=y)
                if symbol == 'S':
                    assert start_position is None
                    start_position = position
                row.append(Pipe(symbol, position, self))
            self.rows.append(row)
            if width is not None:
                assert width == len(row)
            else:
                width = len(row)
        assert start_position is not None
        self.start: Absolute2D = start_position
        self.height: int = len(self.rows)
        assert width is not None
        self.width: int = width
        connected_neighbors = []
        for neighbor in start_position.neighbors():
            for connection in self[neighbor].absolute_connections():
                if connection == start_position:
                    connected_neighbors.append(neighbor)
        assert len(connected_neighbors) == 2
        connected_relative = {other - start_position for other in connected_neighbors}
        start_symbol: Optional[str] = None
        for possible_pipes in ['F', '7', 'J', 'L', '|', '-']:
            if connected_relative == set(Pipe(possible_pipes, Absolute2D(x=0, y=0)).relative_connections()):
                start_symbol = possible_pipes
        assert start_symbol is not None
        self.start: Pipe = Pipe(start_symbol, start_position, self)
        self.rows[start_position.y][start_position.x] = self.start

    def __repr__(self) -> str:
        return str(self)

    def __str__(self) -> str:
        rv = ''
        for y in range(self.height):
            line = ''
            for x in range(self.width):
                line += str(self[Absolute2D(x=x, y=y)])
            if rv:
                rv += '\n'
            rv += line
        return rv

    def __getitem__(self, item: Absolute2D) -> Pipe:
        if item.y < 0 or item.y >= self.height:
            return Pipe('.', item)
        if item.x < 0 or item.x >= self.width:
            return Pipe('.', item)
        return self.rows[item.y][item.x]

    def numbered_string(self, depth: dict[Pipe, int]) -> str:
        rv = ''
        for y in range(self.height):
            line = ''
            for x in range(self.width):
                current_pipe = self[Absolute2D(x=x, y=y)]
                if current_pipe in depth:
                    line += str(depth[current_pipe])[-1]
                else:
                    line += '.'
            if rv:
                rv += '\n'
            rv += line
        return rv


def breadth_first_search(start: Pipe) -> dict[Pipe, int]:
    queued: deque[Pipe] = deque()
    depth: dict[Pipe, int] = {start: 0}
    queued.append(start)
    while queued:
        vertex: Pipe = queued.popleft()
        for neighbor in vertex.connected_pipes():
            if neighbor not in depth:
                depth[neighbor] = depth[vertex] + 1
                queued.append(neighbor)
    return depth


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 10')

    pipes = PipeMap(input_lines(day=10))
    print('pipes :')
    print(pipes)
    start = pipes.start
    print('start :', repr(start))

    depth: dict[Pipe, int] = breadth_first_search(start)
    print(pipes.numbered_string(depth))
    answer1 = max(depth.values())

    print(f'Part 1: {answer1}')
    assert 6725 == answer1

    print('Part 2: TODO')
