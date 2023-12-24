# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

import math
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


def lead_distance(hold_time: int, time: int, distance: int) -> int:
    return - hold_time ** 2 + time * hold_time - distance


def discriminant(time: int, distance: int) -> int:
    return time ** 2 - 4 * distance


def first_positive_near_slope_up(hold_time: int, time: int, distance: int) -> int:
    current = lead_distance(hold_time, time, distance)
    if current >= 0:
        while current >= 0:
            hold_time -= 1
            current = lead_distance(hold_time, time, distance)
        return hold_time + 1
    else:
        while current < 0:
            hold_time += 1
            current = lead_distance(hold_time, time, distance)
        return hold_time


def last_postive_near_slope_down(hold_time: int, time: int, distance: int) -> int:
    current = lead_distance(hold_time, time, distance)
    if current < 0:
        while current < 0:
            hold_time -= 1
            current = lead_distance(hold_time, time, distance)
        return hold_time
    else:
        while current >= 0:
            hold_time += 1
            current = lead_distance(hold_time, time, distance)
        return hold_time - 1


def approx_roots(time: int, distance: int) -> tuple[int, int]:
    disc_root = math.isqrt(discriminant(time, distance))
    return (time - disc_root) // 2, (time + disc_root) // 2


def find_margin(time: int, distance: int) -> int:
    root1, root2 = approx_roots(time, distance)
    first_positive = first_positive_near_slope_up(root1, time, distance)
    last_positive = last_postive_near_slope_down(root2, time, distance)
    answer = last_positive - first_positive + 1
    return answer


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 6')

    actual_time = ''
    actual_distance = ''
    answer1 = 1
    for time, distance in input_pairs():
        answer1 *= find_margin(time, distance)
        actual_time += str(time)
        actual_distance += str(distance)
    print(f'Part 1: {answer1}')
    assert 5133600 == answer1

    actual_time = int(actual_time)
    actual_distance = int(actual_distance)
    answer2 = find_margin(actual_time, actual_distance)
    print(f'Part 2: {answer2}')
    assert 40651271 == answer2
