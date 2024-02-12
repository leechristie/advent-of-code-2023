# Logbook

## Day 9 - Mirage Maintenance

### 1. C

My approach to solving this was to use only one 1-D array and write over the values.

I first worked through the problem on paper, and then chose to implement it in C, because it didn't seem too difficult.

For example, this is my test case that I worked through on paper.

Here it is if you write out the numbers in a grid:

| `x[0]` | `x[1]` | `x[2]` | `x[3]` | `x[4]` | `x[5]` | `x[6]` |
| -----: | -----: | -----: | -----: | -----: | -----: | -----: |
|      1 |      6 |     12 |     19 |     27 |     36 |     46 |
|      5 |      6 |      7 |      8 |      9 |     10 |        |
|      1 |      1 |      1 |      1 |      1 |        |        |
|      0 |      0 |      0 |      0 |        |        |        |

And here is if instead of writing to a new array, you just overwrite the previous row as you go:

| `x[0]` | `x[1]` | `x[2]` | `x[3]` | `x[4]` | `x[5]` | `x[6]` |
| -----: | -----: | -----: | -----: | -----: | -----: | -----: |
|      0 |      0 |      0 |      0 |      1 |     10 |     46 |

The sum of these numbers if the extrapolated value. So we only need $O(n)$ space instead of $O(n^2)$ space.

I don't know if there is a any to calculate this without $O(N^2)$ time though, I can't think of one. So I just wrote a basic recursive function that keeps going until it finds that all the differences are 0. Then in the wrapper / helper function to the recursive call, I sum the numbers.

For Part 2, you could slightly modify the algorithm to extrapolate backwards, but in the summing step you need to alternate adding and subtracting. Instead, it's easier to simply reverse the array and run exactly rhe same extrapolate function.

So Part 2 is simply writing an array reverse function, which I implmented as:

```C
void copy_int_array_backwards(const int * from, int * to, size_t length) {
    size_t i = 0;
    size_t j = length - 1;
    while (i < length)
        to[j--] = from[i++];
}
```

then calling my extrapolate function:

```C
answer2 += extrapolate(backwards, NUMBER_OF_VALUES);
```

### 2. C++

I think I need to go back to Bjarne's book and practice a bit confused working with the `vector` and `string`, I'm not too confident with C++.

Overall, not too difficult to port over my solution to C++ though as Day 9 is a pretty easy implementation, so this day is a good candidate to try some more languages.
