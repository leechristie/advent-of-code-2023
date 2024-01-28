# Logbook

## Day 7 - Camel Cards

### 1. Java (Part 1)

Today's puzzle involves sorting a list of Poker hands in order. The rule for rnaking is not the full Poker hand ranking rule, which I didn't notice in the puzzle description at first and implmented the full Poker rule including for example if comparing the two hands which are both Two Pair: `{Q, Q, 2, 2, 7}` vs `{Q, Q, 2, 2, 6}` I'd compare the high pair, then the low pair, then the single card. It turns out though the puzzle just wants you to compare left to right if the type is the same.

I removed my classes for each type which contains the exact detail of the hands e.g. `TwoPair[high=Q, low=2, single=7]` and converted it to an enum `TwoPair` that doesnt' carry any extra data.

The solution I used then is have the natural ordering of `Hand` be based on compairing the natural ordering of `Ranking` (the name I gave to what the puzzle called "type") first, and then if equal, compare the natural ordering of the list of cards left to right.

For part 2, I added a boolean for the parsing that would set the `'J'` values to `Card.Joker` instead of `Card.Jack`. Since the ranking will be slower, I also added a cached value of `Ranking` to `Hand`.

The logic to work out what card to change the Jokers to TBC...
