// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day01;

import aoc23java.Puzzle;

import java.io.*;
import java.util.*;

public final class Day01 {

    private static final List<String> DIGITS
            = List.of("one", "two", "three", "four", "five", "six", "seven", "eight", "nine");

    private Day01() {
        throw new AssertionError();
    }

    private static OptionalInt getSimpleDigit(String line, int beginIndex) {
        int value = 1;
        for (char c = '1'; c <= '9'; c++) {
            if (line.charAt(beginIndex) == c)
                return OptionalInt.of(value);
            value++;
        }
        return OptionalInt.empty();
    }

    private static OptionalInt getWrittenDigit(String line, int beginIndex) {
        int value = 1;
        for (String s: DIGITS) {
            if (line.indexOf(s, beginIndex) == beginIndex)
                return OptionalInt.of(value);
            value++;
        }
        return OptionalInt.empty();
    }

    private static OptionalInt getDigit(String line, int beginIndex, boolean includeWords) {
        OptionalInt simple = getSimpleDigit(line, beginIndex);
        if (simple.isPresent())
            return simple;
        if (includeWords)
            return getWrittenDigit(line, beginIndex);
        return OptionalInt.empty();
    }

    private static List<Integer> findDigits(String line, boolean includeWords) {
        List<Integer> rv = new ArrayList<>();
        int beginIndex = 0;
        while (beginIndex < line.length()) {
            OptionalInt digit = getDigit(line, beginIndex, includeWords);
            if (digit.isPresent())
                rv.add(digit.getAsInt());
            beginIndex++;
        }
        return rv;
    }

    private static int firstAndLastDigits(List<Integer> digits) {
        return digits.getFirst() * 10 + digits.getLast();
    }

    public static void solve() throws IOException {

        System.out.println("Advent of Code 2023!");
        System.out.println("Day 1");

        int answer1 = 0;
        int answer2 = 0;

        try (BufferedReader in = Puzzle.inputLines(1)) {
            String line;
            while ((line = in.readLine()) != null) {
                answer1 += firstAndLastDigits(findDigits(line, false));
                answer2 += firstAndLastDigits(findDigits(line, true));
            }
        }

        System.out.println("Part 1: " + answer1);
        System.out.println("Part 2: " + answer2);

    }

}
