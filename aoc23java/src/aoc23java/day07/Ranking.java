// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day07;

import java.util.*;

sealed abstract class Ranking implements Comparable<Ranking>
        permits Ranking.FiveOfAKind,
                Ranking.FourOfAKind,
                Ranking.FullHouse,
                Ranking.ThreeOfAKind,
                Ranking.TwoPair,
                Ranking.OnePair,
                Ranking.HighCard,
                Ranking.Unknown {

    static Ranking rank(Hand hand) {
        Objects.requireNonNull(hand);
        Optional<Ranking> ranking;
        if ((ranking = Ranking.FiveOfAKind.attemptRank(hand)).isPresent())
            return ranking.get();
        if ((ranking = Ranking.FourOfAKind.attemptRank(hand)).isPresent())
            return ranking.get();
        // TODO
        return new Ranking.Unknown(); // TODO
    }

    abstract int rankClassIndex();

    static final class FiveOfAKind extends Ranking {

        private final Card card;

        public Card card() {
            return this.card;
        }

        public FiveOfAKind(Card card) {
            super();
            this.card = card;
        }

        @Override
        public int rankClassIndex() {
            return 6;
        }

        @Override
        public String toString() {
            return "Ranking.FiveOfAKind[card=" + this.card + "]";
        }

        private static Optional<Ranking> attemptRank(Hand hand) {
            Objects.requireNonNull(hand);
            for (int i = 1; i < 5; i++)
                if (hand.get(i) != hand.get(0))
                    return Optional.empty();
            return Optional.of(new FiveOfAKind(hand.card0()));
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.FiveOfAKind.class)
                return this.card.compareTo(((FiveOfAKind) other).card);
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

    }

    static final class FourOfAKind extends Ranking {

        private final Card same;
        private final Card different;

        Card same() {
            return same;
        }

        Card different() {
            return different;
        }

        public FourOfAKind(Card same, Card different) {
            super();
            this.same = same;
            this.different = different;
        }

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
            return Optional.of(new FourOfAKind(same, different));
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.FourOfAKind.class) {

                // first compare the card which appears 4 times
                int rv = this.same().compareTo(((FourOfAKind) other).same());
                if (rv != 0)
                    return rv;

                // last compare the other card
                return this.different().compareTo(((FourOfAKind) other).different());

            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        @Override
        public String toString() {
            return "Ranking.FourOfAKind[same=" + this.same + ", different=" + different + "]";
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
            if (other.getClass() == Ranking.FullHouse.class) {
                throw new RuntimeException("TODO: FullHouse ranking");
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
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
            if (other.getClass() == Ranking.ThreeOfAKind.class) {
                throw new RuntimeException("TODO: ThreeOfAKind ranking");
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
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
            if (other.getClass() == Ranking.TwoPair.class) {
                throw new RuntimeException("TODO: TwoPair ranking");
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
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
            if (other.getClass() == Ranking.OnePair.class) {
                throw new RuntimeException("TODO: OnePair ranking");
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
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
            if (other.getClass() == Ranking.HighCard.class) {
                throw new RuntimeException("TODO: HighCard ranking");
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

    }

    static final class Unknown extends Ranking {

        @Override
        public int rankClassIndex() {
            return -1;
        }

        @Override
        public String toString() {
            return "Ranking.Unknown";
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (other.getClass() == Ranking.Unknown.class) {
                return 0;
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

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

}
