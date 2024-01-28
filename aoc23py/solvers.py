# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

from typing import Callable

import day01
import day02
import day03
import day06
import day08

__all__ = ['solvers']

solvers: dict[int, Callable[[], None]] = {
    1: day01.solve,
    2: day02.solve,
    3: day03.solve,
    6: day06.solve,
    8: day08.solve
}
