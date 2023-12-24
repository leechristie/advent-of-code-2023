# Logbook

## Day 6 - Wait For It

### Python

For Part 1, the best thing to do is usually just come up with any solution that works regardless of efficiency so as to reveal the Part 2 as quickly as possible, and the sit and think.

So I simply implement the naive solution of doing exactly what the puzzle example does. This means stepping from 0 to T and calculating the distance traveled, the comparing it to the target distance. This solve part 1 very quickly as the numbers are small, but my expectation is to re-write this for Part 2.

For Part 2, the naive solution does actually work but takes a little under 10 seconds to run on my M1 Pro, which is slower than I'd like.

By looking at the example in Part 1 there is obvious symmetry in the travel times. The first thing I did was rewrite the distance traveled function on paper. This gives a quadratic. By my working, the distance traveled $y$ for a hold time of $x$ given time $T$ and distance $D$ is:

$y=-x^2+Tx-D$

The roots are:

$x=\frac{T\pm\sqrt{T^2-4D}}{2}$

Note that I cleared a negative from numerator and denominator.

The solution will approximately be the distract between the roots. For a quadratic, the distance between the roots is the square root of the discriminant.

This means the solution is approximately $\sqrt{T^2-4D}$, and when I calculate this for the three values in Part 1 and the value in Part 2 the answer is always within $1$ of this value.

However, the puzzle isn't looking for the exact zero, we want the first value of $x$ for which $y>0$ and similarly for the other root.

Instead of just square rooting the discriminant, I find the approximate roots:

$x_1\approx\lfloor(T-isqrt(T^2-4D))/2\rfloor$

$x_2\approx\lfloor(T+isqrt(T^2-4D))/2\rfloor$

Then search nearby for the crossing points. We know near $x_1$ the slope is up and near $x_2$ the slope is down, so we just need to check a couple of nearby values to find the smallest $x$ near $x_1$ that gives positive $y$ and the largest $x$ near $x_2$ that gives positive $y$, and take the difference and add 1, this gives the solution to the problem in constant time so the solution is nearly instant. There also is no floating point math involved since I used `isqrt` and integer division.

I think a slightly less complicated solution that would also work quickly is to binary search from 0 to the turning point of the quadratic and from the turning point to $T$.
