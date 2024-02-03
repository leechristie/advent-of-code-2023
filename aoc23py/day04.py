# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

__all__ = ['solve']

from collections import defaultdict
from typing import Iterator

from puzzle import input_lines, split


def read_input() -> Iterator[tuple[set[int], set[int]]]:
    for line in input_lines(day=4):
        winning, have = line.split(':')[1].split('|')
        winning = split(winning, ' ', int, set, strip=True, remove_doubles=True)
        have = split(have, ' ', int, set, strip=True, remove_doubles=True)
        yield winning, have


def solve() -> None:

    print('Advent of Code 2023')
    print('Day 4')

    answer1 = 0
    answer2 = 0
    index = 1
    card_counts = defaultdict(lambda: 1)
    for winning, have in read_input():

        matches = len(winning & have)

        # origonal scpring function for Part 1 only
        answer1 += 0 if not matches else 2 ** (matches - 1)

        # Part 2 is based on number of cards scratched
        answer2 += card_counts[index]
        
        # update the count of upcomming card for Part 2
        for upcomming in range(index + 1, index + matches + 1):
            card_counts[upcomming] += card_counts[index]

        index += 1

    print(f'Part 1: {answer1}')
    assert 24542 == answer1

    print(f'Part 2: {answer2}')
    assert 8736438 == answer2
