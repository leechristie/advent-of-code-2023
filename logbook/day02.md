# Logbook

## Day 2 - Cube Conundrum

This one seems to have quite an easy part 2. Most of my time on first solving this was spend on Part 1.

And since I did the first solve in Java, I did end up writing it somewhat long-winded parsing code. I parse each day as a

### 1. Java

I parse each day as an integer for the day (this ends up not being needed), and a list of `UnorderedCubes`. An `UnorderedCubes` is a record `UnorderedCubes(int red, int green, int blue)` with the number of red, green, and blue cubes. Most of the code is just parsing.

I was expecting to have to rewrite this with an `OrderedCubes` record in Part 2 and have to do some processing that depends on the order the cubes were used. But Part 2 turned out to be completely trivial. I just write a `minimumCubesFor` function.

```Java
UnorderedCubes minimum = minimumCubesFor(game);
answer2 += minimum.power();
```

### 2. Python

Parsing in Python is a lot more pleasant and both parts only took about 20 minutes.

My code for parsing a set of cube e.g. `blue 1, red 2` into a dictionary `{'blue': 1, 'red': 2}` is:

```Python
def parse_round(r: str) -> MatchRound:
    rv: dict[str, int] = {}
    for cubes in r.split(', '):
        cube_count, cube_color = cubes.split(' ')
        rv[cube_color] = int(cube_count)
    return rv
```

(`MatchRound` is a type alias for `dict[str, int]`)

And then I create a list of these for a line in the input file:

```Python
rounds = [parse_round(r) for r in line.split(': ')[1].split('; ')]
```

Part one is solved by writing a `can_play(rounds: list[MatchRound]) -> bool` function that just loops over each round and checks if any of the match round require more of one cube that is available. Part two calls `power_of(minimum_required(rounds))`. If split this into two steps for simplicity.

Overall, it's a lot smoother to solve these puzzles in Python than Java despite being familiar with both language to around the same extent. However, to be fair, I do tent to write more vlaidation code in Java because I end up being in more of a software engineering mindset when writing Java.
