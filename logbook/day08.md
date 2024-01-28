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

### 1. Python (Part 2) - In Progress

For part 2, I did some optimization to the runtime by converting the strings to ints and therefor the lookup now uses two `list[int]`
instead of `dict[str, tuple[str, str]]`, however, as expected this is not enough to solve the problem.

I'll need to try to figure out another solution, probably something to do with periodicity.

Checking the cycles in ghost state (state = pair of ghost position and direction index):

```
ghost start = HVA, cycle = [2, 15001)
ghost start = HHA, cycle = [4, 20097)
ghost start = BVA, cycle = [3, 17266)
ghost start = RSA, cycle = [4, 16701)
ghost start = AAA, cycle = [2, 12171)
ghost start = NPA, cycle = [2, 20661)
```

This is how long until each ghost gets back to a position it has been before with the 'program counter' for the direction instructions in the header pointing to the same instruction, so ghost `HVA` for example will at step `2` be in the same state as step `15002` (`15001` + `1`).

Unfortnately the cycles are all out of step, so I can't think of any simple way to combine these.

I think I can maybe build generators to jump between the steps where each ghost is at an end position (`'*Z'`), and step through all 6 togethor until they line up.
