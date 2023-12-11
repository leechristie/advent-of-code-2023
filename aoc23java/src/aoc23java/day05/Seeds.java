// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import aoc23java.LongRange;

import java.io.*;
import java.util.*;

final class Seeds {

    private final List<Long> seeds;
    private final List<LongRange> ranges;

    private Seeds(Set<Long> seeds, Set<LongRange> ranges) {
        this.seeds = List.copyOf(seeds);
        this.ranges = List.copyOf(ranges);
    }

    static Seeds parse(String line) {

        // split string on space and convert to list of long
        String[] tokens = line.split(": ")[1].split(" ");
        List<Long> asList = new ArrayList<>();
        for (String token : tokens) {
            long seed = Long.parseLong(token);
            if (seed < 0)
                throw new IllegalArgumentException("negative seed");
            asList.add(seed);
        }
        if (asList.isEmpty())
            throw new IllegalArgumentException("no seeds");

        // convert to set for part 1
        Set<Long> asSet = new TreeSet<>(asList);
        if (asSet.size() != asList.size())
            throw new IllegalArgumentException("duplicate seed");

        // convert to ranges for part 2
        if (asList.size() % 2 != 0)
            throw new IllegalArgumentException("odd number of elements");
        Set<LongRange> rangeSet = new TreeSet<>(Comparator.comparingLong(LongRange::lower));
        for (int i = 0; i < asList.size(); i+=2) {
            long lower = asList.get(i);
            long length = asList.get(i + 1);
            if (lower < 0)
                throw new IllegalArgumentException("negative lower on seeds as ranges");
            if (length <= 0)
                throw new IllegalArgumentException("non-positive length on seeds as ranges");
            long bound = lower + length;
            if (bound <= lower)
                throw new IllegalArgumentException("long overflow on seeds as ranges");
            rangeSet.add(LongRange.ofOpen(lower, bound));
        }

        return new Seeds(asSet, rangeSet);

    }

    static Seeds read(BufferedReader in) throws IOException {
        return Seeds.parse(in.readLine());
    }

    public List<Long> asList() {
        return this.seeds;
    }

    public List<LongRange> asRanges() {
        return this.ranges;
    }

}
