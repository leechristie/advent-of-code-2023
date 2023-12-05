# Logbook

## Day 1 - Gear Ratios

### 1. Python

The most obvious way to approach this puzzle seems to be to load everything into a 2D array, such as in `numpy`. However this year I am avoiding all 3rd party libraries. I could just read each line into a `list[str]` or something like `list[list[Symbol | Number | None]]`, but instead I decided to use a sliding window of 3 lines at a time.

After a bit of refactoring, I now don't track all the numbers found. Instead, I track all of the numbers found in each of the three lines in the sliding window using a deque of three sets. Because I don't need to look at this again except when adding new numbers, I only need to store the column index not the row index or number values.

The inner loop now calls out to a function 9 times to look in each of the positions around the current symbol:

```Python
# check for numbers in those positions
look_for_number(line, column,                 # in arguments
                found, part_numbers, answers  # out arguments
                )
```

The middle call of the 9 will never find anything because the symbol is there, but in this case the function does nothing.

If any new number is found, it is added to the answers for Part 1. If two numbers are found for the same symbol, tracked by `part_numbers`, they are multiplied and added to Part 2. `part_numbers` is set to `None` earlier if the symbol is not `*`.

Some of the changes made are to try to do one pass, and have Part 1 and Part 2 computed together, some are because I was thinking about how I could a C implementation later.
