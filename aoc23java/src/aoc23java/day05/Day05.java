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

        Seeds seeds;
        List<CategoryMapSortedSet> allMaps;
        try (BufferedReader in = Puzzle.inputLines(5)) {
            seeds = Seeds.read(in);
            allMaps = CategoryMapSortedSet.readAll(in);
        }

        long answer1 = solvePart1(seeds, allMaps);
        System.out.println("Part 1: " + answer1);

        long answer2 = solvePart2(seeds, allMaps);
        System.out.println("Part 2: " + answer2);

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

    private static long solvePart2(Seeds seeds, List<CategoryMapSortedSet> allMaps) {
        List<LongRange> ranges = seeds.asRanges();
        for (CategoryMapSortedSet map : allMaps) {
            ranges = map.splitRanges(ranges);
            ranges = map.applyRanges(ranges);
        }
        long answer2 = Long.MAX_VALUE;
        for (LongRange r : ranges)
            if (r.lower() < answer2)
                answer2 = r.lower();
        return answer2;
    }

}
