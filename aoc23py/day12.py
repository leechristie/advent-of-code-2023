# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from enum import Enum
from typing import Union

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

    def __repr__(self) -> str:
        return str(self)

    def __str__(self) -> str:
        if self == SpringState.OPERATIONAL:
            return '.'
        if self == SpringState.DAMAGED:
            return '#'
        if self == SpringState.UNKNOWN:
            return '?'
        raise ValueError(f"invalid spring stat: '{self}'")


class SpringStates:

    __slots__ = ['springs']

    def __init__(self, s: Union[int, 'SpringStates', list[SpringState], str]) -> None:
        if isinstance(s, int):
            self.springs = [SpringState.UNKNOWN] * s
        elif isinstance(s, SpringStates):
            self.springs = list(s.springs)
        elif isinstance(s, list):
            self.springs = list(s)
        elif isinstance(s, str):
            self.springs = [SpringState.parse_symbol(symbol) for symbol in s]
        else:
            raise TypeError

    def __getitem__(self, item: int) -> SpringState:
        return self.springs[item]

    def __setitem__(self, item: int, value: SpringState) -> None:
        self.springs[item] = value

    def __len__(self) -> int:
        return len(self.springs)

    def __repr__(self):
        return str(self)

    def __str__(self):
        rv = ''
        for spring in self.springs:
            rv += str(spring)
        return rv

    def first_unknown(self) -> Union[int, None]:
        if SpringState.UNKNOWN in self.springs:
            return self.springs.index(SpringState.UNKNOWN)
        return None

    def with_next_run(self, length, lower):
        rv = SpringStates(self)
        for i in range(lower):
            if rv[i] == SpringState.UNKNOWN:
                rv[i] = SpringState.OPERATIONAL
        for i in range(lower, lower + length):
            rv[i] = SpringState.DAMAGED
        if lower + length < len(self):
            rv[lower + length] = SpringState.OPERATIONAL
        return rv

    def contradicts(self, other: 'SpringStates') -> bool:
        if not isinstance(other, SpringStates):
            raise TypeError('invalid type for contradicts')
        if len(self) != len(other):
            raise ValueError('length mismatch for contradicts')
        index = 0
        for a, b in zip(self.springs, other.springs):
            if a == SpringState.OPERATIONAL and b == SpringState.DAMAGED:
                return True
            if a == SpringState.DAMAGED and b == SpringState.OPERATIONAL:
                return True
            index += 1
        return False

    def with_unknown_as_operational(self):
        rv = SpringStates(self)
        for index, state in enumerate(rv.springs):
            if state == SpringState.UNKNOWN:
                rv[index] = SpringState.OPERATIONAL
        return rv

    def counts(self) -> list[int]:
        return [len(x) for x in str(self).split('.') if x]


def parse(line: str, multiplier: int = 1) -> tuple[SpringStates, list[int]]:
    springs, numbers = line.split(' ')
    numbers = [int(n) for n in numbers.split(',')]
    springs = '?'.join([springs] * multiplier)
    numbers = numbers * multiplier
    springs = [SpringState.parse_symbol(s) for s in springs]
    return SpringStates(springs), numbers


def count(constraint_springs: SpringStates,
          constraint_numbers: list[int],
          partial_solution: SpringStates,
          remaining: list[int]) -> int:

    # there are no remaining runs of broken springs to assign
    if not remaining:

        # if the solution is non-contradictory, then there is one solution, otherwise none
        return 0 if partial_solution.contradicts(constraint_springs) else 1

    # there is at least one remaining run of broken springs
    current, remaining = remaining[0], remaining[1:]

    # find the first unknown position in the partial solution if there is one
    first_unknown = partial_solution.first_unknown()

    # no way to assign remaining run of broken springs
    if first_unknown is None:
        return 0

    # result (counter the total ways to assign the runs of broken springs)
    total_ways = 0

    # each position `i` for the start of the next run of broken springs
    leave_space = sum(remaining) + len(remaining)
    for i in range(first_unknown, len(constraint_springs) - current + 1 - leave_space):

        # update the partial solution for this new run
        new_partial_solution = partial_solution.with_next_run(length=current, lower=i)

        # only continue to consider this solution if there is no contradiction
        if not new_partial_solution.contradicts(constraint_springs):

            # solution is complete
            if not remaining:

                # get solution
                complete_solution = new_partial_solution.with_unknown_as_operational()
                solution_counts = complete_solution.counts()

                # check solution
                assert solution_counts == constraint_numbers

                # skip current if the solution contradicts
                if complete_solution.contradicts(constraint_springs):
                    continue

                # DEBUGGING - uncomment to print each possible arrangement - DEBUGGING
                #print(complete_solution, solution_counts)

            # recursive call to count out the total ways to arrange the remaining runs
            total_ways += count(constraint_springs,
                                constraint_numbers,
                                new_partial_solution,
                                remaining)

    # return the total count
    return total_ways


def count_helper(constraint_springs: SpringStates,
                 constraint_numbers: list[int]) -> int:
    return count(constraint_springs,
                 constraint_numbers,
                 SpringStates(len(constraint_springs)),
                 list(constraint_numbers))


def solve() -> None:

    print('Advent of Code')
    print('Day 12')

    answer1 = 0
    for line in input_lines(day=12):
        springs, numbers = parse(line)
        answer1 += count_helper(springs, numbers)
    print(f'Part 1: {answer1}')
    assert 7939 == answer1

    answer2 = 0
    i = 1
    for line in input_lines(day=12):
        springs, numbers = parse(line, multiplier=5)
        print(f'{i}. {springs} {numbers}')
        i += 1
        answer2 += count_helper(springs, numbers)
    print(f'Part 2: {answer2}')
