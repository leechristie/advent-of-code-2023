# Advent of Code 2023
# Dr Lee A. Christie
# @0x1ac@techhub.social

import sys
import day01
import day03


def main() -> None:
    arg = sys.argv[-1]
    if arg == '1':
        day01.solve()
    elif arg == '3':
        day03.solve()
    else:
        print('Valid day not specified in command line argument.')
        sys.exit(1)


if __name__ == '__main__':
    main()
