// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java;

import java.io.*;
import java.util.*;
import java.util.function.Consumer;

public final class Puzzle {

    private static final String INPUT_PATH = "../input/";

    private Puzzle() {
        throw new AssertionError();
    }

    public static BufferedReader inputLines(int day) {
        return inputLines(day, false);
    }

    public static BufferedReader inputLines(int day, boolean example) {
        try {
            String dayString = (day < 10 ? "0" : "") + day;
            String prefix = example ? "example" : "input";
            File file = new File(INPUT_PATH + prefix + dayString + ".txt");
            return new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException ex) {
            throw new RuntimeException(ex);
        }
    }

    public static void inputLines(int day, Consumer<String> consumer, boolean example) {
        try (BufferedReader input = Puzzle.inputLines(day, example)) {
            String line;
            while ((line = input.readLine()) != null) {
                consumer.accept(line);
            }
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    public static void inputLines(int day, Consumer<String> consumer) {
        inputLines(day, consumer, false);
    }

    public static Iterable<Character> repeat(String string) {
        if (string.isEmpty()) {
            throw new IllegalArgumentException("cannot repeat empty string");
        }
        final char[] chars = string.toCharArray();
        return () -> new Iterator<>() {
            int index = 0;
            @Override
            public boolean hasNext() {
                return true;
            }
            @Override
            public Character next() {
                char rv = chars[index];
                index = (index + 1) % chars.length;
                return rv;
            }
        };
    }

    public static Iterable<Map.Entry<Integer, Character>> repeatEnumerated(String string) {
        if (string.isEmpty()) {
            throw new IllegalArgumentException("cannot repeat empty string");
        }
        final char[] chars = string.toCharArray();
        return () -> new Iterator<>() {
            int index = 0;
            @Override
            public boolean hasNext() {
                return true;
            }
            @Override
            public Map.Entry<Integer, Character> next() {
                Map.Entry<Integer, Character> rv = Map.entry(index, chars[index]);
                index = (index + 1) % chars.length;
                return rv;
            }
        };
    }


    private static long _gcd(long a, long b) {
        if (a == 0)
            return b;
        if (b == 0)
            return a;
        return _gcd(b, a % b);
    }

    public static long gcd(long a, long b) {
        assert a > 0 && b > 0;
        return _gcd(a, b);
    }

    public static long lcm(long a, long b) {
        assert a > 0 && b > 0;
        return (a * b) / gcd(a, b);
    }

    public static long lcm(Collection<Long> values) {
        long rv = 1;
        for (long value: values)
            rv = lcm(rv, value);
        return rv;
    }

}
