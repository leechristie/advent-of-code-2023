# Logbook

## Day 8 - Haunted Wasteland

### 1. Python

Coming back to Advent of Code 2023 after a long break.

#### Part 1

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

#### Part 2 - First Attempt (Obviously Wrong)

I think you should always start Part 2 by simply throwing the code you have at it and seeing what happens. Sometimes on the early problems, this just works, and on the later ones you can at least learn something about how hard it will be.

Fistly I just ran all 6 "ghosts" from the start points step by step until they are all on end points.

Of course, this is too simple so doesn't solve the problem in any reasonable period of time. I suspect it has something to do with periodicity but don't know exactly how to do this yet. There was at least one problem in AoC 2022 solved by periodicity but I recall that was quite a bit more obvious than in this case, as here we have a graph theory type problem.

#### Part 2 - Second Attempt (A Breif Distraction)

I did some optimization to the runtime by converting the strings to ints and therefor the lookup now uses two `list[int]`
instead of `dict[str, tuple[str, str]]`, however, as expected this is not enough to solve the problem, and I eventually removed this optimization.

However, part of my motivation here was distracting myself thinking about how I would solve it in C later, I won't have such easy access to hash tables, so I will likely do this for simplicity of implementation there, not strictly as an optimization.

#### Part 2 - Third Attempt (Success)

Coming back to the periodicity idea, I look for cycles. I know we can't just look for cycles in the position of the ghost but rather the pairing of the "step" and the ghost position. This is because these two need to be the same for the motion to repeat.

Initially, I ignore when the ghost find an end node (column 3 below), and only record the cycle lengths. But then go back and record the step of the end nodes, and there seems to be only one step in the cycle that is the end state!

| Ghost (Start Position) | Cycle Steps [Lower, Bound) | End Step |
| ---------------------: | :------------------------- | :------- |
|                  `HVA` | $[2, 15001)$               | 14999    |
|                  `HHA` | $[4, 20097)$               | 20093    |
|                  `BVA` | $[3, 17266)$               | 17263    |
|                  `RSA` | $[4, 16701)$               | 16697    |
|                  `AAA` | $[2, 12171)$               | 12169    |
|                  `NPA` | $[2, 20661)$               | 20659    |

If we know that the first one is at an end node at step $14999$, then again at $14999$ plus the length of the cycle and so on. For cycle length $L$ and first stop $S$, the ghost is at an end node at $Ln+S$ for all $n \in \mathbb{Z}$. And the answer is the first step where all ghosts are at an end node. I know there is a mathematical way to solve this but at this point ignore that and go with the "dumber" solution and start at the end step and then increment by the cycle length, until the ghost line up.

This solves the problem, but takes around an hour.

#### Part 2 - Fourth Attempt (Not Dumb)

Now that the second star is earned, I have to fix the "dumb" solution.

It is only now I notice that the $Ln+S$ happens to be (by design of the puzzle setter of course) such that $L=S$ for each ghost. We can now reduce to Sm$ for all $m \in \mathbb{Z}^+$, which means we only need to find the LCM of each of the numbers $S$.

I begin to think of how to find prime divisors of the numbers but then remember that Python has a `math.lcm` function as of Python 3.9.

I do a bunch of tidying up, simplifying code and removing stuff.

After a pre-processing step where we find the ghost periods `ghosts: dict[str, Ghost]`, this is my solution to Part 2:

```Python
answer2 = math.lcm(*[g.stop for g in ghosts.values()])
```

And since I often like to rephrase Part 1 in terms of what is found in Part 2, Part 1 becomes:

```Python
answer1 = ghosts['AAA'].stop
```

### 2. Java

I only spent around an hour implementing the solution in Java. 

The top level logic is the same, but I managed to simplify the solution a bit further because I now know I don't really need to compute the period of the ghost movements, only the step on which they first encounter an end node.

I had to implement my LCM calculation because, unlike Python, it seems there is no built-in LCM function in `java.lang.Math` (except the GCD in `BigInteger`. I simply used the standard recursive definition of GCD I didn't come up with but have seen before where you recurively call `gcd(b, a%b)`, and the identity $LCM(a, b) = |ab| / GCD(a, b)$, although there may be a better way to compute the LCM of multiple number directly.
