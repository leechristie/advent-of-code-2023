# Logbook

## Day 5 - If You Give A Seed A Fertilizer ⭐️

I did Part 1 on the 5th. I was going to leave this for another day but I was curious to find out what Part 2 is about so I solved Part 1 in Java and as I suspected, Part 2 looks a little tricky. I'll probably spend some time thinking about how best to tackle this and then redo Part 1 in one of the other languages and add Part 2 next.

### 1. Java (Part 1)

When I use Java, the parsing code ends up being pretty big.

The lines which contain destination start, source start, and range length I parse into a record `CategoryMap`. My parsing code loads them all into `List<List<CategoryMap>> allMaps` which is not really necessary as all the seeds can be processed step by step as the file is read.

Importantly, assertions in my code check that the source ranges don't overlap for any of the categories, which I needed to check to be sure I can assume this when I do Part 2.

I refactored Part 1 and replaced `List<List<CategoryMap>>` with `List<CategoryMapSortedSet>`. This new `CategoryMapSortedSet` class is a set of `CategoryMap` ordered by `sourceRangeStart`. This is not needed for Part 1, but will be used in my Part 2 solution. I also use an explicitly stored `delta` that is the postive, zero, or negative difference between the source range and destination range.
