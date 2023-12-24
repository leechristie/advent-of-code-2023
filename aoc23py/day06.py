# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social
from typing import Iterator
from puzzle import input_lines


def input_pairs() -> Iterator[tuple[int, int]]:
    lines: list[str] = list(input_lines(day=6))
    assert len(lines) == 2
    assert lines[0].startswith('Time:')
    assert lines[1].startswith('Distance:')
    times: list[int] = [int(t) for t in lines[0].removeprefix('Time:').split(' ') if t]
    distances: list[int] = [int(d) for d in lines[1].removeprefix('Distance:').split(' ') if d]
    return zip(times, distances)


def distance_travelled(hold_time: int, time: int) -> int:
    remaining_time = time - hold_time
    speed = hold_time
    distance = speed * remaining_time
    return distance


def solve_part1(time: int, distance: int) -> int:
    number_of_ways = 0
    for hold_time in range(0, time + 1):
        travelled = distance_travelled(hold_time, time)
        if travelled > distance:
            number_of_ways += 1
    return number_of_ways


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 6')

    actual_time = ''
    actual_distance = ''

    answer1 = 1
    for time, distance in input_pairs():
        answer1 *= solve_part1(time, distance)
        actual_time += str(time)
        actual_distance += str(distance)
    print(f'Part 1: {answer1}')
    assert 5133600 == answer1

    actual_time = int(actual_time)
    actual_distance = int(actual_distance)
    answer2 = solve_part1(actual_time, actual_distance)
    print(f'Part 2: {answer2}')
    assert 40651271 == answer2
