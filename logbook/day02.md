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

### 3. C++

In solving Day 2 in C++ I have written around 100 lines of code dealing with ust parsing the input into some classes representing the data.

I parse to a `Game` object which contains an `int` (the game number) and a `std::vector::<Cubes>` (each of the rounds of the game played.

The cubes are prepresented like this in the input file:

```
3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
```

And I could not figure out how to split strings in C++, so iterated over the positions of `;` in a while loop, then pass the resulting substrings e.g.

```
3 blue, 4 red
```

off to another parsing function as a subtring that loops again on the `,`.

Colors are represented using a `std::array<int, 3>` and I build this by checking the colors against a small `std::array<std::string, 3>` of the color names. There's no point putting 3 values into an `unordered_map` to lookup.

Overall I spent about an hour and a half on parsing code, and then a couple of minutes actually implementing the solve from the parsed objects to the final answers.

I'm not really familiar with C++, and I'm a bit confused about when I'm actually copying things or not, whereas I don't have this confusion when I'm programming in a more familiar language.

### 4. C

Parsing in C was a little more difficult.

I've written some parsing functions which were useful for Day 2 and I think will be useful in the future, for example:

```C
bool read_string_until_any(FILE * file,
                           const char * delimiters,
                           char * buffer,
                           size_t max_length,
                           char * found_delimiter) {
```

This function is called to read from file `file` into string `buffer` (which is a `char[max_length + 1]`) until it encounters one of the specified `delimiters`, e.g.

```C
read_string_until_any(file, ",;\n", buffer, MAX_WORD_SIZE, &found_delimiter)
```

Reads until it encounters {`','`, `';'`, `'\n'`}. The encountered delimiter is returned into the out argument `found_delimiter`. The funtion returns `false` if it encounters `EOF`.

Solution to the problem, I wrote a parsing function which reads a `Game` as defined below:

```C
typedef enum { RED, GREEN, BLUE } Color;

typedef struct {
    int red;
    int green;
    int blue;
} CubeCounter;

typedef struct {
    int id;
    int round_count;
    CubeCounter rounds[MAX_ROUNDS];
} Game;
```

`MAX_ROUNDS` for my input file can be 6. It seems like many of the games are 5 or 6 rounds. I don't want to go allocating for a variable-length data structure yet.

Then it is simple to check if the game is playable (for Part 1), and finding the max of each color to find the minimum number of required cubes and multiply to get the cube power (for Part 2).
