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
