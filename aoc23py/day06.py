# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from puzzle import input_lines


def input_pairs():
    lines = list(input_lines(day=6))
    assert len(lines) == 2
    times = [int(t) for t in lines[0].removeprefix('Time:').split(' ') if t]
    distances = [int(d) for d in lines[1].removeprefix('Distance:').split(' ') if d]
    return zip(times, distances)


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 6')

    for time, distance in input_pairs():
        print(time, distance)

    print(f'Part 1: TODO')
    print(f'Part 2: TODO')
