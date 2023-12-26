// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

public enum Card {

    Ace('A'),
    King('K'),
    Queen('Q'),
    Jack('J'),
    Ten('T'),
    Nine('9'),
    Eight('8'),
    Seven('7'),
    Six('6'),
    Five('5'),
    Four('4'),
    Three('3'),
    Two('2');

    private final char character;

    public static Card parseCard(char character) {
        for (Card card: Card.values())
            if (card.character == character)
                return card;
        throw new IllegalArgumentException("Invalid card: '" + character + "'");
    }

    public char character() {
        return character;
    }

    Card(char character) {
        this.character = character;
    }

}
