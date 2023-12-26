// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day02;

import aoc23java.Puzzle;

import java.io.*;
import java.util.*;

public final class Day02 {

    private Day02() {
        throw new AssertionError();
    }

    public static void solve() {

        System.out.println("Advent of Code 2023!");
        System.out.println("Day 2");

        final UnorderedCubes LIMIT = new UnorderedCubes( 12, 13, 14);

        int answer1 = 0;
        int answer2 = 0;

        try (BufferedReader in = Puzzle.inputLines(2)) {
            String line;
            while ((line = in.readLine()) != null) {
                String[] tokens = line.split(": ");
                assert tokens.length == 2;
                int gameNumber = parseGameNumber(tokens[0]);
                List<UnorderedCubes> game = parseCubeList(tokens[1]);
                if (canPlay(game, LIMIT)) {
                    answer1 += gameNumber;
                }
                UnorderedCubes minimum = minimumCubesFor(game);
                answer2 += minimum.power();
            }
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }

        System.out.println("Part 1: " + answer1);
        System.out.println("Part 2: " + answer2);

        assert 2283 == answer1;
        assert 78669 == answer2;

    }

    private static UnorderedCubes minimumCubesFor(List<UnorderedCubes> game) {
        int red = 0;
        int green = 0;
        int blue = 0;
        for (UnorderedCubes cubes: game) {
            if (cubes.red > red)
                red = cubes.red;
            if (cubes.green > green)
                green = cubes.green;
            if (cubes.blue > blue)
                blue = cubes.blue;
        }
        return new UnorderedCubes(red, green, blue);
    }

    private static boolean canPlay(List<UnorderedCubes> game, UnorderedCubes limit) {
        for (UnorderedCubes cubes: game) {
            if (!cubes.canPlay(limit)) {
                return false;
            }
        }
        return true;
    }

    private static int parseGameNumber(String string) {
        String[] tokens = string.split(" ");
        assert tokens.length == 2;
        assert tokens[0].equals("Game");
        return Integer.parseInt(tokens[1]);
    }

    private static List<UnorderedCubes> parseCubeList(String string) {
        String[] tokens = string.split("; ");
        List<UnorderedCubes> rv = new ArrayList<>();
        for (String token: tokens) {
            rv.add(parseCubes(token));
        }
        return rv;
    }

    private static UnorderedCubes parseCubes(String string) {
        Map<String, Integer> values = new HashMap<>();
        String[] tokens = string.split(", ");
        assert tokens.length <= 3;
        for (String token: tokens) {
            String[] subTokens = token.split(" ");
            assert subTokens.length == 2;
            int count = Integer.parseInt(subTokens[0]);
            String color = subTokens[1];
            values.put(color, count);
        }
        return new UnorderedCubes(values.getOrDefault("red", 0),
                                  values.getOrDefault("green", 0),
                                  values.getOrDefault("blue", 0));
    }

    private record UnorderedCubes(int red, int green, int blue) {

        public UnorderedCubes {
            if (red < 0)
                throw new IllegalArgumentException(
                        "red = " + red + ", expected >= 0");
            if (green < 0)
                throw new IllegalArgumentException(
                        "green = " + green + ", expected >= 0");
            if (blue < 0)
                throw new IllegalArgumentException(
                        "blue = " + blue + ", expected >= 0");
        }

        public boolean canPlay(UnorderedCubes limit) {
            if (this.red > limit.red)
                return false;
            if (this.green > limit.green)
                return false;
            return this.blue <= limit.blue;
        }

        public int power() {
            return red * green * blue;
        }

    }

}
