// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day12;

import java.math.*;
import java.util.*;

public class Day12 {

    private Day12() {
        throw new AssertionError();
    }

    public static void solve() {

        System.out.println("Advent of Code 2023");
        System.out.println("Day 12");

        List<ProblemLine> part1Lines = new ArrayList<>();
        List<ProblemLine> part2Lines = new ArrayList<>();
        ProblemLine.inputLines((ProblemLine problemLine) -> {
            part1Lines.add(problemLine);
            part2Lines.add(problemLine.repeat(5));
        });

        BigInteger answer1 = part1Lines.stream()
                                       .map(ProblemLine::computeNumberOfArrangements)
                                       .reduce(BigInteger.ZERO, BigInteger::add);
        System.out.println("Part 1: " + answer1);
        assert new BigInteger("7939").equals(answer1);

        BigInteger answer2 = part2Lines.stream()
                                       .map(ProblemLine::computeNumberOfArrangements)
                                       .reduce(BigInteger.ZERO, BigInteger::add);
        System.out.println("Part 2: " + answer2);
        assert new BigInteger("850504257483930").equals(answer2);

    }

}
