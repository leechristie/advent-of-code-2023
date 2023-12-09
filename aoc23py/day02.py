# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

from typing import TypeAlias

from puzzle import input_lines


MatchRound: TypeAlias = dict[str, int]


def parse_round(r: str) -> MatchRound:
    rv: dict[str, int] = {}
    for cubes in r.split(', '):
        cube_count, cube_color = cubes.split(' ')
        rv[cube_color] = int(cube_count)
    return rv


AVAILABLE_CUBES = {'red': 12, 'green': 13, 'blue': 14}
COLORS = list(AVAILABLE_CUBES.keys())


def can_play(rounds: list[MatchRound]) -> bool:
    for r in rounds:
        for cube_color, cube_count in r.items():
            if AVAILABLE_CUBES[cube_color] < cube_count:
                return False
    return True


def minimum_required(rounds: list[MatchRound]) -> MatchRound:
    rv = {c: 0 for c in COLORS}
    for r in rounds:
        for c in COLORS:
            if c in r and r[c] > rv[c]:
                rv[c] = r[c]
    return rv


def power_of(param: MatchRound) -> int:
    rv = 1
    for cube_count in param.values():
        rv *= cube_count
    return rv


def solve() -> None:
    answer1 = 0
    answer2 = 0
    for line in input_lines(day=2):
        rounds = [parse_round(r) for r in line.split(': ')[1].split('; ')]
        if can_play(rounds):
            game_id = int(line.split(': ')[0].split(' ')[1])
            answer1 += game_id
        answer2 += power_of(minimum_required(rounds))

    print('Advent of Code 2023')
    print('Day 1')
    print(f'Part 1: {answer1}')
    print(f'Part 2: {answer2}')
