// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import aoc23java.LongRange;

import java.util.*;

final class CategoryMap {

    final LongRange source;
    final LongRange destination;
    final long delta;
    final long length;

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

        this.source = LongRange.ofLength(sourceRangeStart, rangeLength);
        this.destination = LongRange.ofLength(destinationRangeStart, rangeLength);
        this.delta = LongRange.differenceBetweenLowerBounds(this.source, this.destination);
        this.length = rangeLength;
        assert this.source.length() == this.destination.length();

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
        if (source.contains(current))
            return OptionalLong.of(current + delta);
        return OptionalLong.empty();
    }

    public String toString() {
        return this.source + " -> " + this.destination;
    }

}
