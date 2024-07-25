// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day13;

import aoc23java.Puzzle;

import java.io.*;
import java.util.*;

public class Day13 {

    private static final int HORIZONTAL_MULTIPLIER = 100;
    private static final int VERTICAL_MULTIPLIER = 1;

    private Day13() {
        throw new AssertionError();
    }

    public static void solve() {

        System.out.println("Advent of Code 2023");
        System.out.println("Day 13");

        int answer1 = 0;

        List<String> currentLines = new ArrayList<>();

        try (BufferedReader in = Puzzle.inputLines(13)) {
            String line;
            while ((line = in.readLine()) != null) {
                if (line.isEmpty()) {
                    answer1 += process(currentLines);
                    currentLines.clear();
                } else {
                    currentLines.add(line);
                }
            }
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
        if (!currentLines.isEmpty()) {
            answer1 += process(currentLines);
            currentLines.clear();
        }

        System.out.println("Part 1: " + answer1);
        System.out.println("Part 2: TODO");

        assert 34100 == answer1;

    }

    private static int process(final List<String> pattern) {

        OptionalInt result = locateHorizontalReflection(pattern);
        if (result.isPresent()) {
            return result.getAsInt() * HORIZONTAL_MULTIPLIER;
        }
        result = locateVerticalReflection(pattern);
        return result.orElseThrow(
                () -> new RuntimeException("unable to find reflection")
        ) * VERTICAL_MULTIPLIER;

    }

    private static OptionalInt locateHorizontalReflection(final List<String> pattern) {
        for (int firstMirror = 0; firstMirror < pattern.size() - 1; firstMirror++) {
            if (isHorizontalReflection(pattern, firstMirror)) {
                return OptionalInt.of(firstMirror + 1);
            }
        }
        return OptionalInt.empty();
    }

    private static OptionalInt locateVerticalReflection(final List<String> pattern) {
        for (int firstMirror = 0; firstMirror < pattern.getFirst().length() - 1; firstMirror++) {
            if (isVerticalReflection(pattern, firstMirror)) {
                return OptionalInt.of(firstMirror + 1);
            }
        }
        return OptionalInt.empty();
    }

    private static boolean isHorizontalReflection(List<String> pattern, int a) {
        int bound = pattern.size();
        for (int b = a + 1; 0 <= a && a < bound && 0 <= b && b < bound; a--, b++) {
            if (!horizontalRowsMatch(pattern, a, b)) {
                return false;
            }
        }
        return true;
    }

    private static boolean isVerticalReflection(List<String> pattern, int a) {
        int bound = pattern.getFirst().length();
        for (int b = a + 1; 0 <= a && a < bound && 0 <= b && b < bound; a--, b++) {
            if (!verticalColumnsMatch(pattern, a, b)) {
                return false;
            }
        }
        return true;
    }

    private static boolean horizontalRowsMatch(List<String> pattern, int a, int b) {
        return pattern.get(a).equals(pattern.get(b));
    }

    private static boolean verticalColumnsMatch(List<String> pattern, int a, int b) {
        for (String row: pattern) {
            if (row.charAt(a) != row.charAt(b)) {
                return false;
            }
        }
        return true;
    }

}
