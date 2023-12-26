// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import java.util.*;

record PlayedHand(Hand hand, int bid) {

    PlayedHand {
        Objects.requireNonNull(hand);
        if (bid < 1)
            throw new IllegalArgumentException("bid = " + bid + ", expected > 0");
    }

    static PlayedHand parsePlayedHand(String line) {
        Objects.requireNonNull(line);
        String[] tokens = line.split(" ");
        if (tokens.length != 2)
            throw new IllegalArgumentException("line = " + line + ", expected one space");
        int bid = Integer.parseInt(tokens[1]);
        Hand hand = Hand.parseHand(tokens[0]);
        return new PlayedHand(hand, bid);
    }

}
