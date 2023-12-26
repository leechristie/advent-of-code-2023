// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import java.util.Objects;

public record Hand(Card card0, Card card1, Card card2, Card card3, Card card4) {

    public Hand {
        Objects.requireNonNull(card0);
        Objects.requireNonNull(card1);
        Objects.requireNonNull(card2);
        Objects.requireNonNull(card3);
        Objects.requireNonNull(card4);
    }

    public static Hand parseHand(String string) {
        Objects.requireNonNull(string);
        if (string.length() != 5)
            throw new IllegalArgumentException("string = \"" + string + "\", expected, length 5");
        Card[] card = new Card[5];
        for (int i = 0; i < 5; i++)
            card[i] = Card.parseCard(string.charAt(i));
        return new Hand(card[0], card[1], card[2], card[3], card[4]);
    }

}
