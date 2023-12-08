// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

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
        try (BufferedReader in = Puzzle.inputLines(5)) {
            seeds = Seeds.read(in);
            allMaps = CategoryMapSortedSet.readAll(in);
        }

        // calculate Part 1 answer
        long answer1 = Long.MAX_VALUE;
        for (long seed: seeds) {
            long location = CategoryMapSortedSet.applyAll(seed, allMaps);
            if (location < answer1)
                answer1 = location;
        }
        System.out.println("Part 1: " + answer1);

        System.out.println("Part 2: TODO");

    }

}
