// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import java.util.*;

final class CategoryMap {

    final long sourceRangeStart;
    final long sourceRangeBound;
    final long destinationRangeStart;
    final long destinationRangeBound;
    final long rangeLength;
    final long delta;

    CategoryMap(long destinationRangeStart,
                long sourceRangeStart,
                long rangeLength) {
        if (destinationRangeStart < 0)
            throw new IllegalArgumentException(
                    "destinationRangeStart = " + destinationRangeStart + ", expected >= 0");
        if (sourceRangeStart < 0)
            throw new IllegalArgumentException(
                    "sourceRangeStart = " + sourceRangeStart + ", expected >= 0");
        if (rangeLength <= 0)
            throw new IllegalArgumentException(
                    "rangeLength = " + rangeLength + ", expected > 0");
        long destinationRangeBound = destinationRangeStart + rangeLength;
        if (destinationRangeBound <= destinationRangeStart)
            throw new IllegalArgumentException(
                    "long overflow on destination range");
        long sourceRangeBound = sourceRangeStart + rangeLength;
        if (sourceRangeBound <= sourceRangeStart)
            throw new IllegalArgumentException(
                    "long overflow on source range");
        long delta = destinationRangeStart - sourceRangeStart;
        if (sourceRangeBound - 1 + delta != destinationRangeBound - 1)
            throw new IllegalArgumentException(
                    "long overflow on delta");
        this.destinationRangeStart = destinationRangeStart;
        this.destinationRangeBound = destinationRangeBound;
        this.sourceRangeStart = sourceRangeStart;
        this.sourceRangeBound = sourceRangeBound;
        this.rangeLength = rangeLength;
        this.delta = delta;
    }

    static CategoryMap parse(String line) {
        String[] tokens = line.split(" ");
        assert tokens.length == 3;
        long destinationRangeStart = Long.parseLong(tokens[0]);
        long sourceRangeStart = Long.parseLong(tokens[1]);
        long rangeLength = Long.parseLong(tokens[2]);
        return new CategoryMap(destinationRangeStart, sourceRangeStart, rangeLength);
    }

    OptionalLong map(long current) {
        if (current < 0)
            throw new IllegalArgumentException("current = " + current + ", expected >= 0");
        if (current < sourceRangeStart || current >= sourceRangeBound)
            return OptionalLong.empty();
        long offset = current - sourceRangeStart;
        assert offset >= 0;
        assert offset < rangeLength;
        assert current + delta == destinationRangeStart + offset;
        return OptionalLong.of(destinationRangeStart + offset);
    }

    public String toString() {
        StringBuilder rv = new StringBuilder();
        rv.append("[");
        rv.append(this.sourceRangeStart);
        rv.append(", ");
        rv.append(this.sourceRangeBound);
        rv.append(") -> [");
        rv.append(this.destinationRangeStart);
        rv.append(", ");
        rv.append(this.destinationRangeBound);
        rv.append(")");
        return rv.toString();
    }

}
