# Logbook

## Day 1 - Trebuchet?!

I was not planning to try to speed-solve these puzzles but due to being awake at 5:00 a.m. (the release time of the puzzles in GMT) on this one occasion, I was able to complete the puzzle soon after release.

Personal leaderboard times:

- **Part 1**: 2min 29sec (410<sup>th</sup>)
- **Part 2**: 17min 13sec (1,332<sup>nd</sup>)

Part 2 seems to be slightly trickier that previous years. I did have a mistake in my solution that took a little while to spot.

Refactoring and pushing to GitHub was not done until after 9:00 a.m.

The next two days are busy for me so I expect to resume AoC 2023 on day 4, do catch up and hopefully start reimplementing day 1 in another language.

### 1. Python

I first solved the puzzle in Python.

For part one, I looped over the input line and checking each digit against `str.isdigit`, putting them into a list and returning `int(digits[0] + digits[-1])`. In refactoring, I changed the check to `string[0] in '123456789'` as I think zero is not a digit in this puzzle's definition.

For part two, I looped over a list of strings of digits as English words in a function which returned the string with digit stripped off, as in:

```Python
return value, string[len(digit):]
```

However, this was a mistake because the real input file contains overlapping English words. The quickest fix was:

```Python
return value, string[1:]
```

An alternative would be to find the possible merged words and add special cases, but I preferred the clearer implementation without special cases.

In refactoring, I extracted reading of the input to a generator function and created day-specific helper functions I can use in one pass of the input file:

```Python
for line in input_lines(day=1):
    answer1 += first_and_last_digits(find_digits(line))
    answer2 += first_and_last_digits(find_digits(line, include_words=True))
```
