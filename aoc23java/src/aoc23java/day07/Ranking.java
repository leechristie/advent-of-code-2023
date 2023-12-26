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

    static final boolean POKER_RULES = false;

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
            return "Ranking.FiveOfAKind[card=" + this.card() + "]";
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
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.FiveOfAKind.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.FiveOfAKind.class)
                    return this.card.compareTo(((FiveOfAKind) other).card);
            }
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
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.FourOfAKind.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.FourOfAKind.class) {

                    // first compare the card which appears 4 times
                    int rv = this.same().compareTo(((FourOfAKind) other).same());
                    if (rv != 0)
                        return rv;

                    // last compare the other card
                    return this.different().compareTo(((FourOfAKind) other).different());

                }
            }
            assert this.rankClassIndex() != other.rankClassIndex();
            return Integer.compare(this.rankClassIndex(), other.rankClassIndex());
        }

        @Override
        public String toString() {
            return "Ranking.FourOfAKind[same=" + this.same() + ", different=" + this.different() + "]";
        }

    }

    static final class FullHouse extends Ranking {

        private final Card three;
        private final Card pair;

        Card three() {
            return three;
        }

        Card pair() {
            return pair;
        }

        public FullHouse(Card three, Card pair) {
            super();
            this.three = three;
            this.pair = pair;
        }

        @Override
        public int rankClassIndex() {
            return 4;
        }


        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.FullHouse.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.FullHouse.class) {

                    // first compare the card which appears 3 times
                    int rv = this.three().compareTo(((FullHouse) other).three());
                    if (rv != 0)
                        return rv;

                    // last compare the pair
                    return this.pair().compareTo(((FullHouse) other).pair());

                }
            }
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
            return Optional.of(new FullHouse(three, pair));
        }

        @Override
        public String toString() {
            return "Ranking.FullHouse[three=" + this.three() + ", pair=" + this.pair() + "]";
        }

    }

    static final class ThreeOfAKind extends Ranking {

        private final Card three;
        private final Card high;
        private final Card low;

        Card three() {
            return three;
        }

        Card high() {
            return high;
        }

        Card low() {
            return low;
        }

        public ThreeOfAKind(Card three, Card high, Card low) {
            super();
            this.three = three;
            this.high = high;
            this.low = low;
        }

        @Override
        public int rankClassIndex() {
            return 3;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.ThreeOfAKind.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.ThreeOfAKind.class) {

                    // first compare the card which appears 3 times
                    int rv = this.three().compareTo(((ThreeOfAKind) other).three());
                    if (rv != 0)
                        return rv;

                    // then compare the high single card
                    rv = this.high().compareTo(((ThreeOfAKind) other).high());
                    if (rv != 0)
                        return rv;

                    // last compare the low single card
                    return this.low().compareTo(((ThreeOfAKind) other).low());

                }
            }
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
            return Optional.of(new ThreeOfAKind(three, high, low));
        }

        @Override
        public String toString() {
            return "Ranking.ThreeOfAKind[three=" + this.three() + ", high=" + this.high() + ", low=" + this.low() + "]";
        }

    }

    static final class TwoPair extends Ranking {

        private final Card high;
        private final Card low;
        private final Card single;

        Card high() {
            return high;
        }

        Card low() {
            return low;
        }

        Card single() {
            return single;
        }

        public TwoPair(Card high, Card low, Card single) {
            super();
            this.high = high;
            this.low = low;
            this.single = single;
        }

        @Override
        public int rankClassIndex() {
            return 2;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.TwoPair.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.TwoPair.class) {

                    // first compare the high pair
                    int rv = this.high().compareTo(((TwoPair) other).high());
                    if (rv != 0)
                        return rv;

                    // then compare the low pair
                    rv = this.low().compareTo(((TwoPair) other).low());
                    if (rv != 0)
                        return rv;

                    // last compare the single card
                    return this.single().compareTo(((TwoPair) other).single());

                }
            }
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
            return Optional.of(new TwoPair(high, low, single));
        }

        @Override
        public String toString() {
            return "Ranking.TwoPair[high=" + this.high() + ", low=" + this.low() + ", single=" + this.single() + "]";
        }

    }

    static final class OnePair extends Ranking {

        private final Card pair;
        private final Card high;
        private final Card middle;
        private final Card low;

        Card pair() {
            return pair;
        }

        Card high() {
            return high;
        }

        Card middle() {
            return middle;
        }

        Card low() {
            return low;
        }

        public OnePair(Card pair, Card high, Card middle, Card low) {
            super();
            this.pair = pair;
            this.high = high;
            this.middle = middle;
            this.low = low;
        }

        @Override
        public int rankClassIndex() {
            return 1;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.OnePair.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.OnePair.class) {

                    // first compare the pair
                    int rv = this.pair().compareTo(((OnePair) other).pair());
                    if (rv != 0)
                        return rv;

                    // then compare the high single
                    rv = this.high().compareTo(((OnePair) other).high());
                    if (rv != 0)
                        return rv;

                    // then compare the middle single
                    rv = this.middle().compareTo(((OnePair) other).middle());
                    if (rv != 0)
                        return rv;

                    // then compare the low pair
                    return this.low().compareTo(((OnePair) other).low());

                }
            }
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
            return Optional.of(new OnePair(pair, high, middle, low));
        }

        @Override
        public String toString() {
            return "Ranking.OnePair[pair=" + this.pair() + ", high=" + this.high()  + ", middle=" + this.middle() + ", low=" + this.low() + "]";
        }

    }

    static final class HighCard extends Ranking {

        private final Card highest;
        private final Card high;
        private final Card middle;
        private final Card low;
        private final Card lowest;

        Card highest() {
            return highest;
        }

        Card high() {
            return high;
        }

        Card middle() {
            return middle;
        }

        Card low() {
            return low;
        }

        Card lowest() {
            return lowest;
        }

        public HighCard(Card highest, Card high, Card middle, Card low, Card lowest) {
            super();
            this.highest = highest;
            this.high = high;
            this.middle = middle;
            this.low = low;
            this.lowest = lowest;
        }

        @Override
        public int rankClassIndex() {
            return 0;
        }

        @Override
        public int compareTo(Ranking other) {
            Objects.requireNonNull(other);
            if (!POKER_RULES) {
                if (other.getClass() == Ranking.HighCard.class)
                    return this.compareLeftToRight(other);
            } else {
                if (other.getClass() == Ranking.HighCard.class) {

                    // first compare the highest card
                    int rv = this.highest().compareTo(((HighCard) other).highest());
                    if (rv != 0)
                        return rv;

                    // then compare the high card
                    rv = this.high().compareTo(((HighCard) other).high());
                    if (rv != 0)
                        return rv;

                    // then compare the middle card
                    rv = this.middle().compareTo(((HighCard) other).middle());
                    if (rv != 0)
                        return rv;

                    // then compare the low card
                    rv = this.low().compareTo(((HighCard) other).low());
                    if (rv != 0)
                        return rv;

                    // then compare the lowest card
                    return this.lowest().compareTo(((HighCard) other).lowest());

                }
            }
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
            return Optional.of(new HighCard(highest, high, middle, low, lowest));
        }

        @Override
        public String toString() {
            return "Ranking.HighCard[highest=" + this.highest() + ", high=" + this.high()  + ", middle=" + this.middle() + ", low=" + this.low() + ", lowest=" + this.lowest() + "]";
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
