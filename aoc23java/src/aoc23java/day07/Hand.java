// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import java.util.*;
import java.util.function.*;

record Hand(Card card0, Card card1, Card card2, Card card3, Card card4)
        implements Comparable<Hand>, Iterable<Card> {

    Hand {
        Objects.requireNonNull(card0);
        Objects.requireNonNull(card1);
        Objects.requireNonNull(card2);
        Objects.requireNonNull(card3);
        Objects.requireNonNull(card4);
    }

    static Hand parseHand(String string) {
        Objects.requireNonNull(string);
        if (string.length() != 5)
            throw new IllegalArgumentException("string = \"" + string + "\", expected, length 5");
        Card[] card = new Card[5];
        for (int i = 0; i < 5; i++)
            card[i] = Card.parseCard(string.charAt(i));
        return new Hand(card[0], card[1], card[2], card[3], card[4]);
    }

    @Override
    public int compareTo(Hand other) {
        Objects.requireNonNull(other);
        int rv = this.ranking().compareTo(other.ranking());
        if (rv != 0)
            return rv;
        for (int i = 0; i < 5; i++) {
            rv = this.get(i).compareTo(other.get(i));
            if (rv != 0)
                return rv;
        }
        return 0;
    }

    Ranking ranking() {
        return Ranking.rank(this);
    }

    public Card get(int index) {
        if (index == 0)
            return this.card0;
        if (index == 1)
            return this.card1;
        if (index == 2)
            return this.card2;
        if (index == 3)
            return this.card3;
        if (index == 4)
            return this.card4;
        throw new NoSuchElementException("index = " + index + ", expected 0...5");
    }

    @Override
    public void forEach(Consumer<? super Card> action) {
        List.of(card0, card1, card2, card3, card4).forEach(action);
    }

    @Override
    public Spliterator<Card> spliterator() {
        return List.of(card0, card1, card2, card3, card4).spliterator();
    }

    @Override
    public Iterator<Card> iterator() {
        return List.of(card0, card1, card2, card3, card4).iterator();
    }

}
