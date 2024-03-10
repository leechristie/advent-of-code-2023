# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

import time
from enum import Enum
from typing import Union, Optional

from puzzle import input_lines


class SpringState(Enum):

    OPERATIONAL = 0
    DAMAGED = 1
    UNKNOWN = 2

    @staticmethod
    def parse_symbol(symbol: str) -> 'SpringState':
        if symbol == '.':
            return SpringState.OPERATIONAL
        if symbol == '#':
            return SpringState.DAMAGED
        if symbol == '?':
            return SpringState.UNKNOWN
        raise ValueError(f"invalid symbol: '{symbol}'")


class SpringStates:

    __slots__ = ['springs']

    def __init__(self, s: list[SpringState]) -> None:
        if not isinstance(s, list):
            raise TypeError
        self.springs = list(s)

    def __getitem__(self, item: int) -> SpringState:
        return self.springs[item]

    def __setitem__(self, item: int, value: SpringState) -> None:
        self.springs[item] = value

    def __len__(self) -> int:
        return len(self.springs)


def parse(line: str, multiplier: int = 1) -> tuple[SpringStates, list[int]]:
    springs, numbers = line.split(' ')
    numbers = [int(n) for n in numbers.split(',')]
    springs = '?'.join([springs] * multiplier)
    numbers = numbers * multiplier
    springs = [SpringState.parse_symbol(s) for s in springs]
    return SpringStates(springs), numbers


# the number of ways to arrange the given constraint_numbers of runs
# over the given constraint_springs
def number_of_arrangements(constraint_springs: SpringStates,
                           constraint_numbers: list[int]) -> int:

    # noting the len values actually seems to speed up a noticeable little bit
    constraint_springs_length = len(constraint_springs)
    constraint_numbers_length = len(constraint_numbers)

    # memoized return values
    # it was slightly faster to use dict[tuple[int, int], int]
    # than list[list[Optional[int]]] when I tested (and simpler)
    memo: dict[tuple[int, int], int] = dict()

    # the number of ways to arrange the remaining runs of damaged springs
    # on the remaining springs, *assuming we are valid up to this point*
    # this is a closure over the constraints and the memoized return values
    def __number_of_arrangements(lower_spring_index: int,
                                 lower_number_index: int) -> int:

        # check for dynamic memoized return value
        key = (lower_spring_index, lower_number_index)
        rv: Optional[int] = memo.get(key)
        if rv is not None:
            return rv
        rv: int = 0

        # base case - no more to assign, there is only one arrangement (i.e. the no-op)
        if lower_number_index >= constraint_numbers_length:

            # check if there are remaining unsatisfied damaged springs, there are no ways to satisfy constraints
            for i in range(lower_spring_index, constraint_springs_length):
                if constraint_springs[i] == SpringState.DAMAGED:
                    return 0

            # if there are no more unsatisfied, there is 1 way to satisfy constraints
            return 1

        # get the length of the current run of damaged springs
        current = constraint_numbers[lower_number_index]

        # need to leave a space at the end for the remaining runs
        leave_space = 0
        for i in range(lower_number_index + 1, constraint_numbers_length):
            leave_space += 1
            leave_space += constraint_numbers[i]

        # each position `i` for the start of the next run of broken springs
        for i in range(0, constraint_springs_length - current + 1 - leave_space - lower_spring_index):

            # if the next position we cannot add an operational spring,
            # then this is the furthest right the next run can go, stop here
            # not applicable if the start index `i` is 0 relative to the
            # current lower bound `lower_spring_index`
            if i:
                index_of_first_new_operational = lower_spring_index + i - 1
                assert 0 <= index_of_first_new_operational < constraint_springs_length
                if constraint_springs[index_of_first_new_operational] == SpringState.DAMAGED:
                    break

            # find where the run of damaged springs we are adding starts
            run_start = lower_spring_index + i if lower_spring_index else i

            # check each position in the run,
            # if the spring is operational, then continue to next index in outer loop as this is an invalid position
            do_continue = False
            for damaged_index in range(run_start, run_start + current):
                if constraint_springs[damaged_index] == SpringState.OPERATIONAL:
                    do_continue = True
                    break
            if do_continue:
                continue

            # if the next position is not beyond the end of the list then check it
            # if it is damaged, then continue to the next index in the outer look as this is invalid position
            # the next index must be operational as there must be a gap between runs of damaged springs
            final_operational_index = run_start + current
            if final_operational_index < constraint_springs_length:
                if constraint_springs[final_operational_index] == SpringState.DAMAGED:
                    continue

            # recursive call to find the number of ways to assign the remaining
            # runs of damaged springs
            rv += __number_of_arrangements(final_operational_index + 1, lower_number_index + 1)

        # set the memoized return value and return
        memo[key] = rv
        return rv

    # makes the first call the closure with the initial case of (0, 0) - all springs, all numbers
    return __number_of_arrangements(0, 0)


def solve() -> None:

    print('Advent of Code')
    print('Day 12')

    answer1 = 0
    for line in input_lines(day=12):
        springs, numbers = parse(line)
        answer1 += number_of_arrangements(springs, numbers)
    print(f'Part 1: {answer1}')
    assert 7939 == answer1

    answer2 = 0
    for line in input_lines(day=12):
        springs, numbers = parse(line, multiplier=5)
        answer2 += number_of_arrangements(springs, numbers)
    print(f'Part 2: {answer2}')
    assert 850504257483930 == answer2
