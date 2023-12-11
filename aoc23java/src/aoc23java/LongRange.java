// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java;

import java.util.*;

public record LongRange(long lower, long bound) {

    public LongRange {
        if (bound <= lower)
            throw new IllegalArgumentException("empty or invalid range: [" + lower + ", " + bound + " )");
    }

    public static LongRange ofOpen(long lower, long bound) {
        return new LongRange(lower, bound);
    }

    public static LongRange ofLength(long lower, long length) {
        if (length <= 0)
            throw new IllegalArgumentException("length = " + length + ", expected > 0");
        long bound = lower + length;
        if (bound <= lower)
            throw new IllegalArgumentException(
                    "long overflow with primitiveLower = " + lower
                            + ", primitiveLength = " + length);
        return new LongRange(lower, bound);
    }

    public static long differenceBetweenLowerBounds(LongRange from, LongRange to) {

        Objects.requireNonNull(from);
        Objects.requireNonNull(to);

        long difference = to.lower() - from.lower();

        if (from.lower() == to.lower() && difference == 0)
            return difference;
        if (from.lower() < to.lower() && difference > 0)
            return difference;
        if (from.lower() > to.lower() && difference < 0)
            return difference;

        throw new IllegalArgumentException("long overflow on differenceBetweenLowerBounds");

    }

    public boolean contains(long element) {
        return element >= lower && element < bound;
    }

    public Optional<LongRange> intersection(LongRange other) {
        Objects.requireNonNull(other);
        long lower = Math.max(this.lower, other.lower);
        long bound = Math.min(this.bound, other.bound);
        if (lower < bound)
            return Optional.of(LongRange.ofOpen(lower, bound));
        return Optional.empty();
    }

    public long length() {
        return bound - lower;
    }

    @Override
    public String toString() {
        return "[" + lower + ", " + bound + ")";
    }

}
