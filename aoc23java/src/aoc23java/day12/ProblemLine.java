// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day12;

import aoc23java.*;

import java.math.*;
import java.util.*;
import java.util.function.*;

record ProblemLine(String springs, int[] numbers) {

    static void inputLines(Consumer<ProblemLine> consumer) {
        Puzzle.inputLines(12, (String line) -> {
            String[] tokens = line.split(" ");
            if (tokens.length != 2)
                throw new RuntimeException("invalid input line: " + line);
            String[] numbersStr = tokens[1].split(",");
            int[] numbers = new int[numbersStr.length];
            for (int i = 0; i < numbersStr.length; i++)
                numbers[i] = Integer.parseInt(numbersStr[i]);
            consumer.accept(new ProblemLine(tokens[0], numbers));
        });
    }

    public String toString() {
        return "ProblemLine[\"" + springs + "\", numbers=" + Arrays.toString(numbers) + "]";
    }

    public ProblemLine repeat(int n) {
        if (n < 1)
            throw new IllegalArgumentException("n = " + n + ", expected >= 1");
        if (n == 1)
            return this;
        StringBuilder springs = new StringBuilder((this.springs.length() + 1) * n - 1);
        springs.append(this.springs);
        for (int i = 1; i < n; i++) {
            springs.append('?');
            springs.append(this.springs);
        }
        int[] numbers = new int[this.numbers.length * n];
        for (int i = 0; i < n; i++)
            System.arraycopy(this.numbers, 0, numbers, i * this.numbers.length, this.numbers.length);
        return new ProblemLine(springs.toString(), numbers);
    }

    public BigInteger computeNumberOfArrangements() {
        Map<IntTuple, BigInteger> memo = new HashMap<>();
        return computeNumberOfArrangements(memo,
                                           0,
                                           0,
                                           this.springs.length(),
                                           this.numbers.length);
    }

    private BigInteger computeNumberOfArrangements(Map<IntTuple, BigInteger> memo,
                                                   int lowerSpringIndex,
                                                   int lowerNumberIndex,
                                                   int constraintSpringsLength,
                                                   int constraintNumbersLength) {

        // check for dynamic memoized return value
        IntTuple key = new IntTuple(lowerSpringIndex, lowerNumberIndex);
        BigInteger rv = memo.get(key);
        if (rv != null)
            return rv;
        rv = BigInteger.ZERO;

        // base case - no more to assign, there is only one arrangement (i.e. the no-op)
        if (lowerNumberIndex >= constraintNumbersLength) {

            // check if there are remaining unsatisfied damaged springs, there are no ways to satisfy constraints
            for (int i = lowerSpringIndex; i < constraintSpringsLength; i++)
                if (springs.charAt(i) == '#')
                    return BigInteger.ZERO;

            // if there are no more unsatisfied, there is 1 way to satisfy constraints
            return BigInteger.ONE;

        }

        // get the length of the current run of damaged springs
        int current = numbers[lowerNumberIndex];

        // need to leave a space at the end for the remaining runs
        int leaveSpace = 0;
        for (int i = lowerNumberIndex + 1; i < constraintNumbersLength; i++) {
            leaveSpace += 1;
            leaveSpace += numbers[i];
        }

        // each position `i` for the start of the next run of broken springs
        outer: for (int i = 0; i < constraintSpringsLength - current + 1 - leaveSpace - lowerSpringIndex; i++) {

            // if the next position we cannot add an operational spring,
            // then this is the furthest right the next run can go, stop here
            // not applicable if the start index `i` is 0 relative to the
            // current lower bound `lower_spring_index`
            if (i != 0) {
                int indexOfFirstNewOperational = lowerSpringIndex + i - 1;
                assert 0 <= indexOfFirstNewOperational && indexOfFirstNewOperational < constraintSpringsLength;
                if (springs.charAt(indexOfFirstNewOperational) == '#')
                    break;
            }

            // find where the run of damaged springs we are adding starts
            int runStart = (lowerSpringIndex != 0) ? lowerSpringIndex + i : i;

            // check each position in the run,
            // if the spring is operational, then continue to next index in outer loop as this is an invalid position
            for (int damagedIindex = runStart; damagedIindex < runStart + current; damagedIindex++)
                if (springs.charAt(damagedIindex) == '.')
                    continue outer;

            // if the next position is not beyond the end of the list then check it
            // if it is damaged, then continue to the next index in the outer look as this is invalid position
            // the next index must be operational as there must be a gap between runs of damaged springs
            int finalOperationalIndex = runStart + current;
            if (finalOperationalIndex < constraintSpringsLength)
                if (springs.charAt(finalOperationalIndex) == '#')
                    continue;

            // recursive call to find the number of ways to assign the remaining
            // runs of damaged springs
            rv = rv.add(computeNumberOfArrangements(memo,
                                                    finalOperationalIndex + 1,
                                                    lowerNumberIndex + 1,
                                                    constraintSpringsLength,
                                                    constraintNumbersLength));

        }

        // set the memoized return value and return
        memo.put(key, rv);
        return rv;

    }

}
