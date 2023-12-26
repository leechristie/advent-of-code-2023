// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import java.util.*;
import java.util.function.Function;

sealed abstract class Ranking implements Comparable<Ranking>
        permits Ranking.FiveOfAKind,
                Ranking.FourOfAKind,
                Ranking.FullHouse,
                Ranking.ThreeOfAKind,
                Ranking.TwoPair,
                Ranking.OnePair,
                Ranking.HighCard {

    static Ranking rank(Hand hand) {
        Objects.requireNonNull(hand);
        List<Function<Hand, Optional<Ranking>>> rankFunctions
                = List.of(Ranking.FiveOfAKind::attemptRank,
                          Ranking.FourOfAKind::attemptRank,
                          Ranking.FullHouse::attemptRank,
                          Ranking.ThreeOfAKind::attemptRank,
                          Ranking.TwoPair::attemptRank,
                          Ranking.OnePair::attemptRank,
                          Ranking.HighCard::attemptRank);
        Optional<Ranking> ranking;
        for (Function<Hand, Optional<Ranking>> f: rankFunctions)
            if ((ranking = f.apply(hand)).isPresent())
                return ranking.get();
        throw new AssertionError("Unable to rank " + hand);
    }

    abstract int rankClassIndex();

    static final class FiveOfAKind extends Ranking {

        @Override
        public int rankClassIndex() {
            return 6;
        }

        @Override
        public String toString() {
            return "Ranking.FiveOfAKind";
        }

        private static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            for (int i = 1; i < 5; i++)
                if (hand.get(i) != hand.get(0))
                    return Optional.empty();
            return Optional.of(new FiveOfAKind());
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.FiveOfAKind.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

    }

    static final class FourOfAKind extends Ranking {

        @Override
        public int rankClassIndex() {
            return 5;
        }

        private static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            Map<Card, Integer> counter = count(hand);
            if (!Ranking.valuesEquals(counter, 1, 4)) {
                return Optional.empty();
            }
            Card same = Ranking.invertedGet(counter, 4);
            Card different = Ranking.invertedGet(counter, 1);
            return Optional.of(new FourOfAKind());
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.FourOfAKind.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        @Override
        public String toString() {
            return "Ranking.FourOfAKind";
        }

    }

    static final class FullHouse extends Ranking {

        @Override
        public int rankClassIndex() {
            return 4;
        }


        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.FullHouse.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        private static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            Map<Card, Integer> counter = count(hand);
            if (!Ranking.valuesEquals(counter, 2, 3)) {
                return Optional.empty();
            }
            Card three = Ranking.invertedGet(counter, 3);
            Card pair = Ranking.invertedGet(counter, 2);
            return Optional.of(new FullHouse());
        }

        @Override
        public String toString() {
            return "Ranking.FullHouse";
        }

    }

    static final class ThreeOfAKind extends Ranking {

        @Override
        public int rankClassIndex() {
            return 3;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.ThreeOfAKind.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        private static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            Map<Card, Integer> counter = count(hand);
            if (!Ranking.valuesEquals(counter, 1, 1, 3)) {
                return Optional.empty();
            }
            Card three = Ranking.invertedGet(counter, 3);
            List<Card> singles = Ranking.invertedMultiGet(counter, 1);
            Collections.sort(singles);
            assert singles.size() == 2;
            Card low = singles.get(0);
            Card high = singles.get(1);
            return Optional.of(new ThreeOfAKind());
        }

        @Override
        public String toString() {
            return "Ranking.ThreeOfAKind";
        }

    }

    static final class TwoPair extends Ranking {

        @Override
        public int rankClassIndex() {
            return 2;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.TwoPair.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        private static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            Map<Card, Integer> counter = count(hand);
            if (!Ranking.valuesEquals(counter, 1, 2, 2)) {
                return Optional.empty();
            }
            Card single = Ranking.invertedGet(counter, 1);
            List<Card> pairs = Ranking.invertedMultiGet(counter, 2);
            Collections.sort(pairs);
            assert pairs.size() == 2;
            Card low = pairs.get(0);
            Card high = pairs.get(1);
            return Optional.of(new TwoPair());
        }

        @Override
        public String toString() {
            return "Ranking.TwoPair";
        }

    }

    static final class OnePair extends Ranking {

        @Override
        public int rankClassIndex() {
            return 1;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.OnePair.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        public static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            Map<Card, Integer> counter = count(hand);
            if (!Ranking.valuesEquals(counter, 1, 1, 1, 2)) {
                return Optional.empty();
            }
            Card pair = Ranking.invertedGet(counter, 2);
            List<Card> singles = Ranking.invertedMultiGet(counter, 1);
            Collections.sort(singles);
            assert singles.size() == 3;
            Card low = singles.get(0);
            Card middle = singles.get(1);
            Card high = singles.get(2);
            return Optional.of(new OnePair());
        }

        @Override
        public String toString() {
            return "Ranking.OnePair";
        }

    }

    static final class HighCard extends Ranking {

        @Override
        public int rankClassIndex() {
            return 0;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.HighCard.class)
                return this.compareLeftToRight(other);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        public static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            Map<Card, Integer> counter = count(hand);
            if (!Ranking.valuesEquals(counter, 1, 1, 1, 1, 1)) {
                return Optional.empty();
            }
            List<Card> singles = Ranking.invertedMultiGet(counter, 1);
            Collections.sort(singles);
            assert singles.size() == 5;
            Card lowest = singles.get(0);
            Card low = singles.get(1);
            Card middle = singles.get(2);
            Card high = singles.get(3);
            Card highest = singles.get(4);
            return Optional.of(new HighCard());
        }

        @Override
        public String toString() {
            return "Ranking.HighCard";
        }

    }

    int compareLeftToRight(Ranking other) {
        return 0;
    }

    private static Map<Card, Integer> count(Hand hand) {
        Map<Card, Integer> rv = new HashMap<>();
        for (Card c: hand)
            rv.put(c, rv.getOrDefault(c, 0) + 1);
        return rv;
    }

    private static List<Integer> orderedValues(Map<?, Integer> map) {
        List<Integer> rv = new ArrayList<>(map.values());
        Collections.sort(rv);
        return rv;
    }

    private static boolean valuesEquals(Map<?, Integer> map, int... values) {
        List<Integer> valuesList = new ArrayList<>();
        for (int v: values) {
            valuesList.add(v);
        }
        Collections.sort(valuesList);
        return orderedValues(map).equals(valuesList);
    }

    private static <K, V> K invertedGet(Map<K, V> counter, V value) {
        for (Map.Entry<K, V> e: counter.entrySet())
            if (e.getValue().equals(value))
                return e.getKey();
        throw new NoSuchElementException("value not found: " + value);
    }

    private static <K, V> List<K> invertedMultiGet(Map<K, V> counter, V value) {
        List<K> rv = new ArrayList<>();
        for (Map.Entry<K, V> e: counter.entrySet())
            if (e.getValue().equals(value))
                rv.add(e.getKey());
        if (rv.isEmpty())
            throw new NoSuchElementException("value not found: " + value);
        return rv;
    }

}
