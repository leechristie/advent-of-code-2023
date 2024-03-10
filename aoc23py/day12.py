# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social
import sys
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


CONSTRAINT_SPRINGS: Optional[SpringStates] = None
CONSTRAINT_NUMBERS: Optional[list[int]] = None
CONSTRAINT_SPRINGS_LENGTH: Optional[int] = None
CONSTRAINT_NUMBERS_LENGTH: Optional[int] = None
CONSTRAINT_MEMO: dict[tuple[int, int], int] = dict()


def print_numbers(n: int) -> None:
    for i in range(n):
        s = str(i)[-1]
        print(s, end='')
    print()


# number of arrangements possible with remaining springs, numbers
# given that the previous index is a '.' (operational)
# and given that the previous indices don't contradict the springs constraint
def number_of_arrangements(lower_spring_index: int,
                           lower_number_index: int) -> int:

    # get the problem parameters from the global setup
    global CONSTRAINT_SPRINGS
    global CONSTRAINT_NUMBERS
    global CONSTRAINT_SPRINGS_LENGTH
    global CONSTRAINT_NUMBERS_LENGTH
    global CONSTRAINT_MEMO

    assert CONSTRAINT_SPRINGS is not None
    assert CONSTRAINT_NUMBERS is not None
    assert CONSTRAINT_SPRINGS_LENGTH is not None
    assert CONSTRAINT_NUMBERS_LENGTH is not None
    assert CONSTRAINT_MEMO is not None

    key = (lower_spring_index, lower_number_index)
    rv = CONSTRAINT_MEMO.get(key)
    if rv is not None:
        return rv

    # print(f'{CONSTRAINT_SPRINGS = }')
    # print(f'{CONSTRAINT_NUMBERS = }')
    # print(f'{CONSTRAINT_SPRINGS_LENGTH = }')
    # print(f'{CONSTRAINT_NUMBERS_LENGTH = }')
    # print(f'{lower_spring_index = }')
    # print(f'{lower_number_index = }')

    if lower_number_index >= CONSTRAINT_NUMBERS_LENGTH:
        #print(f'there are no numbers because {lower_number_index = } which is outside [0, {CONSTRAINT_NUMBERS_LENGTH})')
        for i in range(lower_spring_index, CONSTRAINT_SPRINGS_LENGTH):
            if CONSTRAINT_SPRINGS[i] == SpringState.DAMAGED:
                #print(f'index {i} is damages, cannot do, returning 0')
                return 0
        #print(f'no damaged from index {lower_spring_index} on, can do, returning 1')
        return 1

    current = CONSTRAINT_NUMBERS[lower_number_index]

    #print(f'{current = }')
    #print(f'remaining = {CONSTRAINT_NUMBERS[lower_number_index + 1:]}')

    # need to leave a space at the end for the remaining runs
    leave_space = 0
    for i in range(lower_number_index + 1, CONSTRAINT_NUMBERS_LENGTH):
        leave_space += 1
        leave_space += CONSTRAINT_NUMBERS[i]
    #print(f'{leave_space = }')

    number_of_ways = 0

    # # each position `i` for the start of the next run of broken springs
    #print(f'{lower_spring_index = }')
    broke_because_start_dot = False
    for i in range(0, CONSTRAINT_SPRINGS_LENGTH - current + 1 - leave_space - lower_spring_index):

        #print()
        #print(f'{i = }')

        # if the next position we cannot add an operational spring,
        # then this is the furthest right the next run can go, stop here
        # not applicable if the start index `i` is 0 relative to the
        # current lower bound `lower_spring_index`
        if i:
            index_of_first_new_operational = lower_spring_index + i - 1
            assert 0 <= index_of_first_new_operational < CONSTRAINT_SPRINGS_LENGTH
            # print(f'{index_of_first_new_operational = }')
            if CONSTRAINT_SPRINGS[index_of_first_new_operational] == SpringState.DAMAGED:
                #print(f'stopping at {i = }')
                broke_because_start_dot = True
                break
            else:
                pass  #print(f'start dot at index {index_of_first_new_operational} is okay')

        # display the current and next
        #print(CONSTRAINT_SPRINGS, '<-- constraints')
        leave_start = 0
        temp = ''
        count_before_first_hash = 0
        if lower_spring_index:
            temp += 'o' * (lower_spring_index - 1)  # non-contradictory and fixed (unknown to this stack frame)
            temp += ','  # single non-contradictory '.' (operational)
            leave_start += lower_spring_index
            count_before_first_hash += lower_spring_index
        temp += '.' * i  # speculative - '.' (operational)
        count_before_first_hash += i
        temp += '#' * current  # speculative - current position
        if leave_space:
            temp += ','  # the first leave space will be a '.'
            temp += '!' * (leave_space - 1)  # leave space for remaining
        #print(f'{temp} <- current plan')
        #print(f'{count_before_first_hash = }')

        run_start = count_before_first_hash
        run_end = run_start + current
        do_continue = False
        for damaged_index in range(run_start, run_end):
            # print(f'# at index {damaged_index}', end='')
            #print(f'will check position {damaged_index} to ensure can be damaged')
            if CONSTRAINT_SPRINGS[damaged_index] == SpringState.OPERATIONAL:
                #print(f'position {damaged_index} - IS CONTRADICTORY because it cannot be damaged!')
                do_continue = True
                break
        if do_continue:
            #print('continuing to next')
            continue

        final_operational_index = count_before_first_hash + current
        if final_operational_index < CONSTRAINT_SPRINGS_LENGTH:
            # print(f'. at index {lower_number_index + i + current}', end='')
            if CONSTRAINT_SPRINGS[final_operational_index] == SpringState.DAMAGED:
                #print(f'end dot position {final_operational_index} - IS CONTRADICTORY because it cannot be operational!')
                continue
            else:
                #print(f'end dot position {final_operational_index} - is okay because it can be operational!')
                pass  # print(' is okay')

        #print_numbers(CONSTRAINT_SPRINGS_LENGTH)
        #print(CONSTRAINT_SPRINGS)
        #print(f'{temp} <- current plan')
        #print(f'    number_of_arrangements({final_operational_index + 1}, {lower_number_index + 1})')
        #print()
        number_of_ways += number_of_arrangements(final_operational_index + 1, lower_number_index + 1)

    if broke_because_start_dot:
        pass #print('broke because start dot')

    CONSTRAINT_MEMO[key] = number_of_ways
    return number_of_ways


def count_setup2(constraint_springs: SpringStates,
                 constraint_numbers: list[int]) -> None:

    # store problem parameters
    global CONSTRAINT_SPRINGS
    global CONSTRAINT_NUMBERS
    global CONSTRAINT_SPRINGS_LENGTH
    global CONSTRAINT_NUMBERS_LENGTH
    global CONSTRAINT_MEMO
    CONSTRAINT_SPRINGS = constraint_springs
    CONSTRAINT_NUMBERS = constraint_numbers
    CONSTRAINT_SPRINGS_LENGTH = len(constraint_springs)
    CONSTRAINT_NUMBERS_LENGTH = len(constraint_numbers)
    CONSTRAINT_MEMO = dict()


def count_helper2(constraint_springs: SpringStates,
                  constraint_numbers: list[int]) -> int:
    count_setup2(constraint_springs, constraint_numbers)
    return number_of_arrangements(0, 0)


def solve() -> None:

    print('Advent of Code')
    print('Day 12')

    # for line in input_lines(day=12):
    #     springs, numbers = parse(line)
    #     springs[5] = SpringState.DAMAGED
    #     if count_helper(springs, numbers) >= 70:
    #         print(f'actual answer = {count_helper2(springs, numbers)}')
    #         print(f'expected answer = {count_helper(springs, numbers)}')
    #         break

    # springs = SpringStates('??????#???.?????#?#???????####??????#?#??...#.?????')
    # numbers = [2, 2, 1, 2, 5, 1, 4]
    # start = time.perf_counter()
    # print(f'actual answer = {count_helper2(springs, numbers)}')
    # print(f'time = {time.perf_counter() - start}')
    # start = time.perf_counter()
    # print(f'expected answer = {count_helper(springs, numbers)}')
    # print(f'time = {time.perf_counter() - start}')

    start = time.perf_counter()
    answer1 = 0
    for line in input_lines(day=12):
        springs, numbers = parse(line)
        answer1 += count_helper2(springs, numbers)
    print(f'Part 1: {answer1}')
    print(f'time = {time.perf_counter() - start}')
    assert 7939 == answer1

    answer2 = 0
    i = 1
    for line in input_lines(day=12):
        springs, numbers = parse(line, multiplier=5)
        print(f'{i}. {springs} {numbers}')
        i += 1
        current = count_helper2(springs, numbers)
        print(f'Current: {current}.')
        answer2 += current
        print(f'Running Total: {answer2} . . . ')
        print()
    print(f'Part 2: {answer2}')
