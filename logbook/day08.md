# Logbook

## Day 8 - Haunted Wasteland

### 1. Python

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

Checking the cycles in ghost state (state = pair of ghost position and direction index).

This is how long until each ghost gets back to a position it has been before with the 'program counter' for the direction instructions in the header pointing to the same instruction, so ghost `HVA` for example will at step $2$ be in the same state as step $15002$.

There seems to be only once step in the cycle that is the end state.

| Ghost (Start Position) | Cycle Steps [Lower, Bound) | End Step |
| ---------------------: | :------------------------- | :------- |
|                  `HVA` | $[2, 15001)$               | 14999    |
|                  `HHA` | $[4, 20097)$               | 20093    |
|                  `BVA` | $[3, 17266)$               | 17263    |
|                  `RSA` | $[4, 16701)$               | 16697    |
|                  `AAA` | $[2, 12171)$               | 12169    |
|                  `NPA` | $[2, 20661)$               | 20659    |

So if we have a cycle $[lower, bound)$ which is at end step at $end$, then we have end steps every $(bound-lower)n+end$ for all non-negative integer $n$.

I think there may be a mathematical way like Euclid's algorithm to find when each of the 6 sequences are at an end step, but I don't know how.

So instead, I step through each sequence advancing the one in the back, and this eventually solves the problem after some amount of time, earning the second star.

However, it seems that the condition $bound-lower = end$ holds for each of these, which means the formula reduce to simpler periods $end \times m$ for all positive integer $m$, which I think I can solve mathematically a lot more easily than the $An+B$ form, and will come back to very soon and try to make this way faster!
