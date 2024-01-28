# Logbook

## Day 8 - Haunted Wasteland

### 1. Python (Part 1)

Coming back to Advent of Code 2023 after a long break.

In Part 1, I create a `dict` mapping the current node to the two next possible nodes.

I created a helper function to loop over the header string forever:

```Python
def infinite_repeat(iterable: Iterable[T]) -> Iterator[T]:
    while True:
        yield from iterable
```

There might be some `itertools` function that does this already though?

Anyway, Part 1 is quite simple, just keep stepping through until you reach `'ZZZ'`. The core of the solution is:

```Python
for direction in infinite_repeat(header):
   current = left[current] if direction == 'L' else right[current]
   answer1 += 1
   if current == end:
       break
```

For part 2, I did some optimization to the runtime by converting the strings to ints and therefor the lookup now uses two `list[int]`
instead of `dict[str, tuple[str, str]]`, however, as expected this is not enough to solve the problem.

I'll need to try to figure out another solution, probably something to do with periodicity.
