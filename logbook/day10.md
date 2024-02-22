# Logbook

## Day 10 - Pipe Maze

### 1. Python

This puzzle was quite fun.

The first part is just running breadth first search on a maze of pipes. So the main challenge is just parsing the pipes and representing it somehow. The volume of code did start to get away a little.

In Part 2, since you need to do some kind of floor fill (the BFS is apropreate), but tracking sides of the pipe sperate. My solution was to split the pipe sections into 4 quadrents, for example the `'L'` shape becomes:

```
'▐', '▙',
'▝', '▀'
```

Then fill from the outside to identify which quadrents are "outside".

Then just loop over the tiles that were a 2x2 of empty quadrents and see which are not in the outside set.

There is room for improvements, for example, having the BFS just write the outside status to the `Quadrent` objects directly instead of trakcing a visited set, amoung many other possible improvments.
