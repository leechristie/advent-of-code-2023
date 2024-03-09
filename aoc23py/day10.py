# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from puzzle import *


class Pipe:

    def __init__(self, symbol: str, position: Absolute2D, pipes: Optional['PipeMap'] = None) -> None:
        assert symbol in ('F', '7', 'J', 'L', '-', '|', '.', 'S'), f'invalid symbol \'{symbol}\''
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

    def expand_edge(self):
        new_width = self.width + 2
        new_height = self.height + 2
        new_header = [Pipe('.', Absolute2D(x=x, y=0), self) for x in range(new_width)]
        new_rows = [new_header]
        for old_y, row in enumerate(self.rows):
            new_row = [Pipe('.', Absolute2D(x=0, y=old_y+1), self)]
            for old_x, pipe in enumerate(row):
                assert pipe.position.x == old_x
                assert pipe.position.y == old_y
                new_row.append(Pipe(pipe.symbol, Absolute2D(x=old_x+1, y=old_y+1), self))
            new_row.append(Pipe('.', Absolute2D(x=new_width-1, y=old_y+1), self))
            new_rows.append(new_row)
        new_footer = [Pipe('.', Absolute2D(x=x, y=new_height-1), self) for x in range(new_width)]
        new_rows.append(new_footer)
        self.rows = new_rows
        self.start = Pipe(self.start.symbol, self.start.position + Relative2D(dx=1, dy=1), self)
        self.width = new_width
        self.height = new_height

    def create_fill_map(self, depth: Iterable[Pipe]) -> list[list[bool]]:
        fill_map = []
        for y in range(self.height):
            fill_row = []
            for x in range(self.width):
                if self[Absolute2D(x=x, y=y)] in depth:
                    fill_row.append(True)
                else:
                    fill_row.append(False)
            fill_map.append(fill_row)
        return fill_map

    def destroy_unexplored(self, explored: Iterable[Pipe]):
        for y in range(self.height):
            for x in range(self.width):
                position = Absolute2D(x=x, y=y)
                if self[position] not in explored:
                    self[position].symbol = '.'


symbol_map: dict[str, list[str]] = {
    '|': ['▐', '▌',
          '▐', '▌'],
    '-': ['▄', '▄',
          '▀', '▀'],
    'F': ['▗', '▄',
          '▐', '▛'],
    '7': ['▄', '▖',
          '▜', '▌'],
    'J': ['▟', '▌',
          '▀', '▘'],
    'L': ['▐', '▙',
          '▝', '▀'],
    '.': ['?', ' ',
          ' ', ' ']
}


valid_directions: dict[str, set[Relative2D]] = {
    '?': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT},
    ' ': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT},
    '▐': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT},
    '▌': {Relative2D.UP, Relative2D.DOWN, Relative2D.RIGHT},
    '▄': {Relative2D.UP, Relative2D.LEFT, Relative2D.RIGHT},
    '▀': {Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT},
    '▜': {Relative2D.DOWN, Relative2D.LEFT},
    '▙': {Relative2D.UP, Relative2D.RIGHT},
    '▟': {Relative2D.UP, Relative2D.LEFT},
    '▛': {Relative2D.DOWN, Relative2D.RIGHT},
    '▖': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT},
    '▗': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT},
    '▘': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT},
    '▝': {Relative2D.UP, Relative2D.DOWN, Relative2D.LEFT, Relative2D.RIGHT}
}


class Quadrent:

    def __init__(self, symbol: str, position: Absolute2D, pipes: 'QuadrentPipeMap'):
        self.symbol = symbol
        self.position = position
        self.pipes = pipes

    def __str__(self):
        return self.symbol

    def __repr__(self):
        return self.symbol

    def neighbours(self) -> Iterator['Quadrent']:
        for direction in valid_directions[self.symbol]:
            neighbour_position = self.position + direction
            if neighbour_position in self.pipes:
                yield self.pipes[neighbour_position]


class QuadrentPipeMap:

    def __init__(self, pipes: PipeMap) -> None:
        self.height = pipes.height * 2
        self.width = pipes.width * 2
        self.quadrents: list[list[Quadrent]] = [[Quadrent(' ', Absolute2D(x=x, y=y), self) for x in range(self.width)] * self.width for y in range(self.height)]
        for y in range(pipes.height):
            for x in range(pipes.width):
                pipe = pipes[Absolute2D(x=x, y=y)]
                top_left = Absolute2D(x=x*2, y=y*2)
                self.set_four_quadrents(top_left, pipe.symbol)

    def set_four_quadrents(self, top_left: Absolute2D, symbol: str):
        symbols = symbol_map[symbol]
        top_right = top_left + Relative2D.RIGHT
        bottom_left = top_left + Relative2D.DOWN
        bottom_right = bottom_left + Relative2D.RIGHT
        self[top_left].symbol = symbols[0]
        self[top_right].symbol = symbols[1]
        self[bottom_left].symbol = symbols[2]
        self[bottom_right].symbol = symbols[3]

    def __getitem__(self, position: Absolute2D) -> Quadrent:
        return self.quadrents[position.y][position.x]

    def __setitem__(self, position: Absolute2D, value: Quadrent) -> None:
        self.quadrents[position.y][position.x] = value

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

    def __contains__(self, position: Absolute2D) -> bool:
        return 0 <= position.y < self.height and 0 <= position.x < self.width

    def label_in_out(self, outside) -> int:
        count_inside = 0
        for y in range(0, self.height, 2):
            for x in range(0, self.width, 2):
                top_left = Absolute2D(x=x, y=y)
                quadrent = self[top_left]
                if quadrent.symbol == '?':
                    if quadrent in outside:
                        quadrent.symbol = 'O'
                    else:
                        quadrent.symbol = 'I'
                        count_inside += 1
        return count_inside


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


def breadth_first_search_quadrents(start: Quadrent) -> dict[Quadrent, int]:
    queued: deque[Quadrent] = deque()
    depth: dict[Quadrent, int] = {start: 0}
    queued.append(start)
    while queued:
        vertex: Quadrent = queued.popleft()
        for neighbor in vertex.neighbours():
            if neighbor not in depth:
                depth[neighbor] = depth[vertex] + 1
                queued.append(neighbor)
    return depth


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 10')

    pipes = PipeMap(input_lines(day=10))
    pipes.expand_edge()
    start = pipes.start
    depth: dict[Pipe, int] = breadth_first_search(start)
    answer1 = max(depth.values())
    print(f'Part 1: {answer1}')
    assert 6725 == answer1

    pipes.destroy_unexplored(depth.keys())
    quadrent_pipes = QuadrentPipeMap(pipes)
    outside: dict[Quadrent, int] = breadth_first_search_quadrents(quadrent_pipes[Absolute2D(x=0, y=0)])
    answer2 = quadrent_pipes.label_in_out(outside.keys())
    # print(quadrent_pipes)

    print(f'Part 2: {answer2}')
    assert 383 == answer2
