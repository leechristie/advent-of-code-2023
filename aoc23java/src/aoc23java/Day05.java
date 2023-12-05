package aoc23java;

import java.io.*;
import java.util.*;

public final class Day05 {

    private Day05() {
        throw new AssertionError();
    }

    public static void solve() throws IOException {

        ProblemSpecification spec = readInput();
        long answer1 = Long.MAX_VALUE;
        for (long seed: spec.seeds()) {
            long location = mapSeedToLocation(seed, spec.maps());
            assert location >= 0;
            if (location < answer1) {
                answer1 = location;
            }
        }

        System.out.println("Advent of Code 2023!");
        System.out.println("Day 5");
        System.out.println("Part 1: " + answer1);
        System.out.println("Part 2: TODO");

    }

    private static long mapSeedToLocation(long seed,
                                          List<List<CategoryMap>> spec) {
        long current = seed;
        for (List<CategoryMap> maps: spec) {
            current = mapToNext(current, maps);
        }
        return current;
    }

    private static long mapToNext(long current,
                                  List<CategoryMap> maps) {
        OptionalLong rv = OptionalLong.empty();
        for (CategoryMap map: maps) {
            OptionalLong newValue = map.map(current);
            assert rv.isEmpty() || newValue.isEmpty();
            if (rv.isEmpty()) {
                rv = newValue;
            }
        }
        return rv.orElse(current);
    }

    private static ProblemSpecification readInput() throws IOException {

        try (BufferedReader in = Puzzle.inputLines(5)) {

            List<Long> seeds = parseSeeds(in.readLine());

            String line;
            List<List<CategoryMap>> allMaps = new ArrayList<>();
            List<CategoryMap> currentMaps = new ArrayList<>();
            while ((line = in.readLine()) != null) {
                if (line.endsWith("map:") || line.isBlank()) {
                    if (!currentMaps.isEmpty()) {
                        allMaps.add(currentMaps);
                        assert !hasSourceOverlaps(currentMaps);
                        currentMaps = new ArrayList<>();
                    }
                } else {
                    currentMaps.add(CategoryMap.parseCategoryMap(line));
                }
            }
            if (!currentMaps.isEmpty()) {
                assert !hasSourceOverlaps(currentMaps);
                allMaps.add(currentMaps);
            }

            return new ProblemSpecification(seeds, allMaps);

        }

    }

    private static boolean hasSourceOverlaps(List<CategoryMap> currentMaps) {
        for (int ai = 0; ai < currentMaps.size() - 1; ai++) {
            CategoryMap a = currentMaps.get(ai);
            for (int bi = ai + 1; bi < currentMaps.size(); bi++) {
                CategoryMap b = currentMaps.get(bi);
                if (overlaps(a, b)) {
                    return true;
                }
            }
        }
        return false;
    }

    private static boolean overlaps(CategoryMap a, CategoryMap b) {
        if (a.sourceRangeBound() <= b.sourceRangeStart) {
            return false;
        }
        if (b.sourceRangeBound() <= a.sourceRangeStart) {
            return false;
        }
        return true;
    }

    private record ProblemSpecification(List<Long> seeds, List<List<CategoryMap>> maps) {}

    private static List<Long> parseSeeds(String line) {
        String[] tokens = line.split(": ")[1].split(" ");
        List<Long> rv = new ArrayList<>();
        for (int i = 0; i < tokens.length; i++) {
            rv.add(Long.parseLong(tokens[i]));
        }
        return rv;
    }

    private record CategoryMap(long destinationRangeStart,
                               long sourceRangeStart,
                               long rangeLength) {

        long sourceRangeBound() {
            return sourceRangeStart + rangeLength;
        }

        CategoryMap {
            assert destinationRangeStart >= 0;
            assert sourceRangeStart >= 0;
            assert rangeLength > 0;
            assert destinationRangeStart + rangeLength > destinationRangeStart;
            assert sourceRangeStart + rangeLength > sourceRangeStart;
        }

        static CategoryMap parseCategoryMap(String line) {
            String[] tokens = line.split(" ");
            assert tokens.length == 3;
            long destinationRangeStart = Long.parseLong(tokens[0]);
            long sourceRangeStart = Long.parseLong(tokens[1]);
            long rangeLength = Long.parseLong(tokens[2]);
            return new CategoryMap(destinationRangeStart, sourceRangeStart, rangeLength);
        }

        public OptionalLong map(long current) {
            if (current < sourceRangeStart) {
                return OptionalLong.empty();
            }
            if (current >= sourceRangeBound()) {
                return OptionalLong.empty();
            }
            long offset = current - sourceRangeStart;
            assert offset >= 0;
            assert offset < rangeLength;
            return OptionalLong.of(destinationRangeStart + offset);
        }

    }

}
