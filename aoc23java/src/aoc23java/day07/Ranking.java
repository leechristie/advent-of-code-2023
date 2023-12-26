// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import java.util.*;

enum Ranking {

    HighCard(List.of(1, 1, 1, 1, 1)),
    OnePair(List.of(1, 1, 1, 2)),
    TwoPair(List.of(1, 2, 2)),
    ThreeOfAKind(List.of(1, 1, 3)),
    FullHouse(List.of(2, 3)),
    FourOfAKind(List.of(1, 4)),
    FiveOfAKind(List.of(5));

    private final List<Integer> orderedCounts;

    Ranking(List<Integer> orderedCounts) {
        this.orderedCounts = orderedCounts;
    }

    final boolean hasRank(Map<Card, Integer> counter) {
        return valuesEquals(counter, orderedCounts);
    }

    private static Map<Card, Integer> count(Hand hand) {
        Map<Card, Integer> rv = new HashMap<>();
        for (Card c: hand)
            rv.put(c, rv.getOrDefault(c, 0) + 1);
        return rv;
    }

    private static boolean valuesEquals(Map<?, Integer> map, List<Integer> orderedValues) {
        return orderedValues(map).equals(orderedValues);
    }

    private static List<Integer> orderedValues(Map<?, Integer> map) {
        List<Integer> rv = new ArrayList<>(map.values());
        Collections.sort(rv);
        return rv;
    }

    private static List<Ranking> RANKINGS_WORST_TO_BEST = new ArrayList<>(Arrays.asList(Ranking.values()));
    private static List<Ranking> RANKINGS_BEST_TO_WORST = RANKINGS_WORST_TO_BEST.reversed();

    static Ranking rank(Hand hand) {
        Map<Card, Integer> counter = count(hand);
        for (Ranking ranking: RANKINGS_BEST_TO_WORST)
            if (ranking.hasRank(counter))
                return ranking;
        throw new AssertionError("Unable to rank " + hand);
    }

}
