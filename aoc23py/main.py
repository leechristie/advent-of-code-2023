# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

import sys
from solvers import *


def main() -> None:
    
    try:
        day = int(sys.argv[-1])
        solver = solvers[day]
    except (ValueError, KeyError):
        print('Valid day not specified in command line argument.')
        sys.exit(1)

    solver()


if __name__ == '__main__':
    main()
