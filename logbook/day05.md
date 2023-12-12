# Logbook

## Day 5 - If You Give A Seed A Fertilizer

I did Part 1 on the 5th. I was going to leave this for another day but I was curious to find out what Part 2 is about so I solved Part 1 in Java and as I suspected, Part 2 looks a little tricky. This is the first puzzle this year where Part 2 is a bit time-consuming.

Part 1 just involves parsing the input file, which as I chose Java first was slightly annoying, then for each seed apply it to each map in turn. A map is stored with a source range and destination range and precomputed delta between the source and destination. Is a seed is contained in the range, add the delta, if not, don't. After mapping all seed, find the smalles value.

For Part 2, the number of seeds to map is around 1.5 billion, so using brute force won't really work. My approch is to take all seed ranges as a list of ranges and apply those to each category map sorted set in turn, yielding a new list of ranges. Where an entire range doesn't fit cleanly into a map range we need to split the input range that is being mapped. For my input, we start with 10 ranges and after each mapping end up with 71 ranges. If the number of maps had exploded to a huge number, I would have then optimised the solution by seeing if we can join ranges that overlap (there may be ranges which overlap at some point as they pass through the category maps and those could be joined), but 71 is small. I loop over the lower bounds on all 71 output ranges and get the smallest. The solver runs nearly instantly and gives the corect result.

### 1. Java

When I use Java, the parsing code ends up being pretty big.

The lines which contain destination start, source start, and range length I parse into a record `CategoryMap`. My parsing code loads them all into `List<List<CategoryMap>> allMaps` which is not really necessary as all the seeds can be processed step by step as the file is read.

Importantly, assertions in my code check that the source ranges don't overlap for any of the categories, which I needed to check to be sure I can assume this when I do Part 2.

I refactored Part 1 and replaced `List<List<CategoryMap>>` with `List<CategoryMapSortedSet>`. This new `CategoryMapSortedSet` class is a set of `CategoryMap` ordered by `sourceRangeStart`. This is not needed for Part 1, but will be used in my Part 2 solution. I also use an explicitly stored `delta` that is the postive, zero, or negative difference between the source range and destination range.

For part 2 I add an `asRanges` method to `Seeds` which interprets the seed list as ranges. I refactored my Part 1 solution to use a record to represent a range (`LongRange`). Then I wrote a `CategoryMapSortedSet::splitRange` method which takes a `LongRange` and returns a `List<LongRange>` where the ranges are split on the start and end points of the ranges in the category map sorted set.

The logic of `splitRange` was hard to implement correctly so I first wrote a `mapsWhereSourceIncludesRange` method to exclude some ranges which are not overlapping the incomming range to make it easier to write. One thing that helped was making the `LongRange` strict and throw exceptions on empty or backwards ranges. This helps find bugs.
