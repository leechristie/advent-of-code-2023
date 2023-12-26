// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import aoc23java.Puzzle;

import javax.print.attribute.HashDocAttributeSet;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;

public final class Day07 {

    private Day07() {
        throw new AssertionError();
    }

    public static void solve() {

        System.out.println("Advent of Code 2023!");
        System.out.println("Day 7");
        System.out.println("Part 1: TODO");
        System.out.println("Part 2: TODO");

        for (Card c: Card.values()) {
            System.out.println(c + ", " + c.character() + ", " + Card.parseCard(c.character()));
        }

        try (BufferedReader in = Puzzle.inputLines(7)) {
            String line;
            while ((line = in.readLine()) != null) {
                String[] tokens = line.split(" ");
                assert tokens.length == 2;
                int bid = Integer.parseInt(tokens[1]);
                Hand hand = Hand.parseHand(tokens[0]);
                System.out.println(hand + "\t" + bid);
            }
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }

    }

}
