// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

enum Card {

    Two('2'),
    Three('3'),
    Four('4'),
    Five('5'),
    Six('6'),
    Seven('7'),
    Eight('8'),
    Nine('9'),
    Ten('T'),
    Jack('J'),
    Queen('Q'),
    King('K'),
    Ace('A');

    private final char character;

    static Card parseCard(char character) {
        for (Card card: Card.values())
            if (card.character == character)
                return card;
        throw new IllegalArgumentException("Invalid card: '" + character + "'");
    }

    char character() {
        return character;
    }

    Card(char character) {
        this.character = character;
    }

}
