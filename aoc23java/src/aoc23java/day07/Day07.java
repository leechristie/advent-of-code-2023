// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import aoc23java.Puzzle;

import java.io.*;
import java.util.*;

public final class Day07 {

    private Day07() {
        throw new AssertionError();
    }

    public static void solve() {

        System.out.println("Advent of Code 2023");
        System.out.println("Day 7");

        List<PlayedHand> playedHands = readPlayedHands(false);
        playedHands.sort(Comparator.comparing(PlayedHand::hand));
        long answer1 = computePart1(playedHands);
        System.out.println("Part 1: " + answer1);
        assert 246795406 == answer1;

        List<PlayedHand> playedHandsWithJokers = readPlayedHands(true);
        System.out.println("Part 2: TODO");

    }

    private static long computePart1(List<PlayedHand> playedHands) {
        long rv = 0;
        int rank = 1;
        for (PlayedHand playedHand: playedHands) {
            rv += rank * (long) playedHand.bid();
            assert rv > 0;
            rank++;
        }
        return rv;
    }

    private static List<PlayedHand> readPlayedHands(boolean jokers) {
        List<PlayedHand> rv = new ArrayList<>();
        try (BufferedReader in = Puzzle.inputLines(7, false)) {
            String line;
            while ((line = in.readLine()) != null)
                rv.add(PlayedHand.parsePlayedHand(line, jokers));
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
        return rv;
    }

}
