# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social
from typing import Iterator, Optional
from puzzle import input_lines, infinite_repeat
import tqdm

__all__ = ['solve']


def read_header(file: Iterator[str]) -> str:
    rv = next(file)
    assert next(file) == ''  # expect blank line seperator
    return rv


def read_body(file: Iterator[str]) -> Iterator[tuple[str, tuple[str, str]]]:
    for line in file:
        lhs, line = line.replace(' ', '').split('=')
        x, y = line.strip('()').split(',')
        yield lhs, (x, y)


START = 'AAA'
END = 'ZZZ'


class IncremenetingLookupTable:

    def __init__(self):
        self.next_id = 0
        self.lookup_table: dict[str, int] = {}
        self.reverse_lookup_table: list[str] = []

    def lookup(self, string: str) -> int:
        value: Optional[int] = self.lookup_table.get(string, None)
        if value is not None:
            return value
        self.lookup_table[string] = self.next_id
        self.reverse_lookup_table.append(string)
        self.next_id += 1
        return self.next_id - 1

    def reverse(self, integer: int) -> str:
        return self.reverse_lookup_table[integer]


def optimize(body: dict[str, tuple[str, str]]) -> tuple[int, int, list[int], list[int], list[bool], list[int], IncremenetingLookupTable]:
    n = len(body)
    left = [-1] * n
    right = [-1] * n
    is_ghost_stop = [False] * n
    ghosts: list[int] = []
    lookup = IncremenetingLookupTable()
    for lhs, rhs in body.items():
        x, y = rhs
        ghost = False
        if lhs.endswith('A'):
            ghost = True
        stop = False
        if lhs.endswith('Z'):
            stop = True
        lhs = lookup.lookup(lhs)
        x = lookup.lookup(x)
        y = lookup.lookup(y)
        left[lhs] = x
        right[lhs] = y
        is_ghost_stop[lhs] = stop
        if ghost:
            ghosts.append(lhs)
    start = lookup.lookup('AAA')
    end = lookup.lookup('ZZZ')
    return start, end, left, right, is_ghost_stop, ghosts, lookup


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 8')

    file = input_lines(day=8)
    header = read_header(file)

    body: dict[str, tuple[str, str]] = {}
    for lhs, rhs in read_body(file):
        body[lhs] = rhs

    # optimize the body for fast lookup
    start, end, left, right, is_ghost_stop, ghosts_current, lookup = optimize(body)

    answer1 = 0
    current = start
    for direction in infinite_repeat(header):
        assert direction in ('L', 'R')
        current = left[current] if direction == 'L' else right[current]
        answer1 += 1
        if current == end:
            break
    print(f'Part 1: {answer1}')
    assert 12169 == answer1

    # investigating state cycles for Part 2 ...
    previous_states: dict[tuple[int, int], int] = {}
    for ghost_start in ghosts_current:
        steps = 0
        current_position = ghost_start
        for next_index, next_direction in infinite_repeat(header, enumerated=True):

            # recording the current state
            state = current_position, next_index
            if state in previous_states:
                print('ghost start = ', lookup.reverse(ghost_start), ', cycle = [', previous_states[state], ', ', steps, ')', sep='')
                break
            else:
                previous_states[state] = steps

            # moving to the nxt state
            steps += 1
            current_position = left[current_position] if next_direction == 'L' else right[current_position]
