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

### 2. Java

I decided to do the second implementation the same day.

The solution is similar to my refactored Python solution. However, in my python `strip_digit` I return a tuple of the digit and the remaining string to be parsed. Now I know we always strip only one character off, I decided to use a `beginIndex` variable that lives in the loop instead of delegating incrementing to the strip function. This also means I don't need to find a way to return a tuple, and it means I don't keep creating substrings.

The main different idea here is the `getWrittenDigit` method:

```Java
int value = 1;
for (String s: DIGITS) {
    if (line.indexOf(s, beginIndex) == beginIndex)
        return OptionalInt.of(value);
    value++;
}
return OptionalInt.empty();
```

I call two version of the get digit functions like this, however, I think there may be a less ugly way to combine the two resulting `OptionalInt` that I couldn't think of:

```Java
OptionalInt simple = getSimpleDigit(line, beginIndex);
if (simple.isPresent())
    return simple;
if (includeWords)
    return getWrittenDigit(line, beginIndex);
return OptionalInt.empty();
```

### 3. C

Started by solving Day 1 Part 1 in C. Will return to Part 2 and refactor solution later.
