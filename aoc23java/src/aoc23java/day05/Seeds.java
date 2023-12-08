// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import java.io.*;
import java.util.*;

public final class Seeds implements Iterable<Long> {

    private final List<Long> seeds;

    private Seeds(Set<Long> seeds) {
        this.seeds = List.copyOf(seeds);
    }

    public static Seeds of(Collection<Long> seeds) {
        Set<Long> copy = Set.copyOf(seeds);
        if (copy.size() != seeds.size())
            throw new IllegalArgumentException("duplicate seed");
        for (long l: copy)
            if (l < 0)
                throw new IllegalArgumentException("negative seed");
        return new Seeds(copy);
    }

    public static Seeds parse(String line) {
        String[] tokens = line.split(": ")[1].split(" ");
        Set<Long> rv = new TreeSet<>();
        for (int i = 0; i < tokens.length; i++) {
            long seed = Long.parseLong(tokens[i]);
            if (seed < 0)
                throw new IllegalArgumentException("negative seed");
            rv.add(seed);
        }
        if (rv.size() != tokens.length)
            throw new IllegalArgumentException("duplicate seed");
        return new Seeds(rv);
    }

    public static Seeds read(BufferedReader in) throws IOException {
        return Seeds.parse(in.readLine());
    }

    @Override
    public Iterator<Long> iterator() {
        return seeds.iterator();
    }

}
