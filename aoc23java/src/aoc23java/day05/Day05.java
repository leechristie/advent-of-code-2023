// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import aoc23java.LongRange;
import aoc23java.Puzzle;

import java.io.*;
import java.util.*;

public final class Day05 {

    private Day05() {
        throw new AssertionError();
    }

    public static void solve() throws IOException {

        System.out.println("Advent of Code 2023!");
        System.out.println("Day 5");

        // read input file
        Seeds seeds;
        List<CategoryMapSortedSet> allMaps;
        try (BufferedReader in = Puzzle.inputLines(5, true)) {
            seeds = Seeds.read(in);
            allMaps = CategoryMapSortedSet.readAll(in);
        }

        long answer1 = solvePart1(seeds, allMaps);
        System.out.println("Part 1: " + answer1);
        assert 35 == answer1;
        //assert 157211394 == answer1;

        // TODO: finish implementing the fast solve for part 2
        long answer2 = slowSolvePart2(seeds, allMaps);
        System.out.println("Part 2: " + answer2);
        assert 46 == answer2;

    }

    private static long slowSolvePart2(Seeds seeds, List<CategoryMapSortedSet> allMaps) {
        long answer2 = Long.MAX_VALUE;
        System.out.println("solving part 2");
        for (LongRange range: seeds.asRanges()) {
            System.out.println(range);
            List<Long> temp = new ArrayList<>();
            for (long seed = range.lower(); seed < range.bound(); seed++) {
                long location = CategoryMapSortedSet.applyAll(seed, allMaps);
                if (location < answer2)
                    answer2 = location;
                temp.add(location);
            }
            System.out.println(range + " mapped to " + temp.toString().replace('[', '{').replace(']', '}'));
        }
        return answer2;
    }

    private static long solvePart1(Seeds seeds, List<CategoryMapSortedSet> allMaps) {
        long answer1 = Long.MAX_VALUE;
        for (long seed: seeds.asList()) {
            long location = CategoryMapSortedSet.applyAll(seed, allMaps);
            if (location < answer1)
                answer1 = location;
        }
        return answer1;
    }

}
