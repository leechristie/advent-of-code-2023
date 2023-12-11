// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import aoc23java.LongRange;

import java.io.*;
import java.util.*;

final class CategoryMapSortedSet
        implements Iterable<CategoryMap> {

    private List<CategoryMap> cachedOrder = null;

    private final SortedSet<CategoryMap> maps = new TreeSet<>(
            Comparator.comparing((x) -> x.source.lower())
    );

    static long applyAll(long seed, List<CategoryMapSortedSet> allMapSets) {
        long rv = seed;
        for (CategoryMapSortedSet mapSet : allMapSets)
            rv = mapSet.apply(rv);
        assert rv >= 0;
        return rv;
    }

    static List<CategoryMapSortedSet> readAll(BufferedReader in) throws IOException {
        String line;
        List<CategoryMapSortedSet> rv = new ArrayList<>();
        CategoryMapSortedSet currentMaps = new CategoryMapSortedSet();
        while ((line = in.readLine()) != null) {
            if (line.endsWith("map:") || line.isBlank()) {
                if (!currentMaps.isEmpty()) {
                    rv.add(currentMaps);
                    currentMaps = new CategoryMapSortedSet();
                }
            } else
                currentMaps.add(CategoryMap.parse(line));
        }
        if (!currentMaps.isEmpty())
            rv.add(currentMaps);
        return rv;
    }

    boolean isEmpty() {
        return maps.isEmpty();
    }

    void add(CategoryMap map) {
        cachedOrder = null;
        maps.add(map);
    }

    @Override
    public Iterator<CategoryMap> iterator() {
        if (cachedOrder == null) {
            cachedOrder = List.copyOf(maps);
            validateCacheForOverlap();
        }
        return cachedOrder.iterator();
    }

    private void validateCacheForOverlap() {
        for (int i = 0; i < cachedOrder.size() - 1; i++) {
            CategoryMap map1 = cachedOrder.get(i);
            CategoryMap map2 = cachedOrder.get(i + 1);
            assert map1.source.lower() < map2.source.lower(); // sort order
            if (map2.source.lower() < map1.source.bound()) // no overlap
                throw new IllegalStateException("overlap in source ranges");
        }
    }

    long apply(long current) {
        OptionalLong rv = OptionalLong.empty();
        for (CategoryMap map: this) {
            OptionalLong newValue = map.map(current);
            assert rv.isEmpty() || newValue.isEmpty();
            if (rv.isEmpty() && newValue.isPresent())
                rv = newValue;
        }
        return rv.orElse(current);
    }

    private List<CategoryMap> mapsWhereSourceIncludesRange(LongRange range) {
        List<CategoryMap> rv = new ArrayList<>();
        for (CategoryMap current : this) {
            if (current.source.bound() <= range.lower())
                continue;
            if (current.source.lower() >= range.bound())
                continue;
            rv.add(current);
        }
        return rv;
    }

    List<LongRange> splitRange(LongRange range) {

        Objects.requireNonNull(range);

        List<CategoryMap> maps = mapsWhereSourceIncludesRange(range);
        if (maps.isEmpty())
            return new ArrayList<>();

        List<LongRange> rv = new ArrayList<>(maps.size() * 2 + 1);
        if (maps.getFirst().source.lower() > range.lower()) {
            rv.add(LongRange.ofOpen(range.lower(), maps.getFirst().source.lower()));
        }
        for (int i = 0; i < maps.size(); i++) {
            CategoryMap current = maps.get(i);
            rv.add(current.source.intersection(range)
                          .orElseThrow(() -> new AssertionError("expected range to overlap")));
            int j = i + 1;
            if (j < maps.size()) {
                CategoryMap next = maps.get(i);
                rv.add(LongRange.ofOpen(current.source.bound(), next.source.lower()));
            }
        }
        if (maps.getLast().source.bound() < range.bound()) {
            rv.add(LongRange.ofOpen(maps.getLast().source.bound(), range.bound()));
        }
        return rv;

    }

}
