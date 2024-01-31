# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

import math
from collections import defaultdict
from typing import Iterator, Optional
from puzzle import input_lines, infinite_repeat

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


def preprocess_body(body: dict[str, tuple[str, str]])\
        -> tuple[dict[str, str], dict[str, str], dict[str, bool], list[str]]:
    left: dict[str, str] = {}
    right: dict[str, str] = {}
    is_stop: dict[str, bool] = defaultdict(lambda: False)
    starts: list[str] = []
    for lhs, rhs in body.items():
        x, y = rhs
        ghost = False
        if lhs.endswith('A'):
            ghost = True
        stop = False
        if lhs.endswith('Z'):
            stop = True
        left[lhs] = x
        right[lhs] = y
        is_stop[lhs] = stop
        if ghost:
            starts.append(lhs)
    return left, right, is_stop, starts


class Ghost:

    def __init__(self, lower: int, bound: int, stop: int):
        self.lower = lower
        self.bound = bound
        self.stop = stop
        self.length = bound - lower
        assert (self.length == self.stop), f'Ghost cycle len = {self.length}, stop = {self.stop}, expected equal'

    def __repr__(self):
        return f'GhostCycle(lower={self.lower}, bound={self.bound}, stop={self.stop})'

    def __str__(self):
        return repr(self)

    def __len__(self):
        return self.length


def find_ghost_cycles(header, body) -> dict[str, Ghost]:
    left, right, is_ghost_stop, ghosts_current = preprocess_body(body)
    ghost_cycles = {}
    for ghost_start in ghosts_current:
        previous_states = {}
        steps_to_is_end = {}
        steps = 0
        current_position = ghost_start
        for next_index, next_direction in infinite_repeat(header, enumerated=True):

            # recording the current state
            steps_to_is_end[steps] = is_ghost_stop[current_position]
            state = current_position, next_index
            if state in previous_states:
                end_step = None
                for i in range(previous_states[state], steps):
                    if steps_to_is_end[i]:
                        assert end_step is None
                        end_step = i
                assert end_step is not None
                ghost_cycles[ghost_start] = Ghost(previous_states[state], steps, end_step)
                break
            else:
                previous_states[state] = steps

            # moving to the nxt state
            steps += 1
            current_position = left[current_position] if next_direction == 'L' else right[current_position]

    return ghost_cycles


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 8')

    file = input_lines(day=8)
    header = read_header(file)
    body: dict[str, tuple[str, str]] = {lhs: rhs for lhs, rhs in read_body(file)}
    ghosts: dict[str, Ghost] = find_ghost_cycles(header, body)

    # Part 1
    answer1 = ghosts['AAA'].stop
    print(f'Part 1: {answer1}')
    assert 12169 == answer1

    # Part 2
    answer2 = math.lcm(*[g.stop for g in ghosts.values()])
    print(f'Part 2: {answer2}')
    assert 12030780859469 == answer2
