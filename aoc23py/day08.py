# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social
import time
from collections import defaultdict
from types import NoneType
from typing import Iterator, Optional, NewType
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


class DummyLUT:

    def __init__(self):
        pass

    def lookup(self, string: str) -> str:
        return string

    def reverse(self, string: str) -> str:
        return string


StringBody = NewType('StringBody', tuple[str, str, dict[str, str], dict[str, str], dict[str, bool], list[str], DummyLUT])
IntBody = NewType('IntBody', tuple[int, int, list[int], list[int], list[bool], list[int], IncremenetingLookupTable])


def _dont_optimize(body: dict[str, tuple[str, str]]) -> StringBody:
    n = len(body)
    left: dict[str, str] = {}
    right: dict[str, str] = {}
    is_ghost_stop: dict[str, bool] = defaultdict(lambda: False)
    ghosts: list[str] = []
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
        is_ghost_stop[lhs] = stop
        if ghost:
            ghosts.append(lhs)
    start = 'AAA'
    end = 'ZZZ'
    return StringBody((start, end, left, right, is_ghost_stop, ghosts, DummyLUT()))


def _optimize(body: dict[str, tuple[str, str]]) -> IntBody:
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
    return IntBody((start, end, left, right, is_ghost_stop, ghosts, lookup))


def process_body(body: dict[str, tuple[str, str]], optimize: bool = False) -> IntBody | StringBody:
    if optimize:
        return _optimize(body)
    return _dont_optimize(body)


class GhostCycle:

    def __init__(self, lower: int, bound: int, stop: int):
        self.lower = lower
        self.bound = bound
        self.stop = stop
        self.length = bound - lower

    def __repr__(self):
        return f'GhostCycle(lower={self.lower}, bound={self.bound}, stop={self.stop})'

    def __str__(self):
        return repr(self)

    def __len__(self):
        return self.length


def find_ghost_cycles(ghosts_current, header, is_ghost_stop, left, right):

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
                ghost_cycles[ghost_start] = GhostCycle(previous_states[state], steps, end_step)
                break
            else:
                previous_states[state] = steps

            # moving to the nxt state
            steps += 1
            current_position = left[current_position] if next_direction == 'L' else right[current_position]

    return ghost_cycles


def arg_min(d):
    if not d:
        raise ValueError
    minimum = min(d.values())
    for k, v in d.items():
        if v == minimum:
            return k
    raise AssertionError


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 8')

    file = input_lines(day=8)
    header = read_header(file)

    body: dict[str, tuple[str, str]] = {}
    for lhs, rhs in read_body(file):
        body[lhs] = rhs

    # optimize the body for fast lookup
    start, end, left, right, is_ghost_stop, ghosts_current, lookup = process_body(body, optimize=True)

    timer = time.perf_counter()

    # Part 1
    answer1 = 0
    current = start
    for direction in infinite_repeat(header):
        current = left[current] if direction == 'L' else right[current]
        answer1 += 1
        if current == end:
            break
    print(f'Part 1: {answer1}')
    assert 12169 == answer1

    # Part 2
    ghost_cycles = find_ghost_cycles(ghosts_current, header, is_ghost_stop, left, right)
    ghosts_current = {ghost_start: cycle.stop for (ghost_start, cycle) in ghost_cycles.items()}
    progress = tqdm.tqdm(desc='Part 2')
    progress_value = 0
    set_size = len(set(ghosts_current.values()))
    best_set_size = set_size
    while set_size > 1:
        earliest_ghost = arg_min(ghosts_current)
        ghosts_current[earliest_ghost] += len(ghost_cycles[earliest_ghost])
        new_progress = min(ghosts_current.values())
        progress.update(new_progress - progress_value)
        progress_value = new_progress
        set_size = len(set(ghosts_current.values()))
        if set_size < best_set_size:
            progress.set_description(f'best set size {set_size} at progress value {progress_value}')
            best_set_size = set_size
    answer2, = set(ghosts_current.values())
    print(f'Part 2: {answer2}')
    assert 12030780859469 == answer2

    print('Time :', (time.perf_counter() - timer))
