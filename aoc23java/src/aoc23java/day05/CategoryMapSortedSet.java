// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day05;

import java.io.*;
import java.util.*;

public final class CategoryMapSortedSet
        implements Iterable<CategoryMap> {

    private List<CategoryMap> cachedOrder = null;

    private final SortedSet<CategoryMap> maps = new TreeSet<>(
            Comparator.comparing((x) -> x.sourceRangeStart)
    );

    public static long applyAll(long seed, List<CategoryMapSortedSet> allMapSets) {
        long rv = seed;
        for (CategoryMapSortedSet mapSet: allMapSets)
            rv = mapSet.apply(rv);
        assert rv >= 0;
        return rv;
    }

    public static List<CategoryMapSortedSet> readAll(BufferedReader in) throws IOException {
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
            assert map1.sourceRangeStart < map2.sourceRangeStart; // sort order
            if (map2.sourceRangeStart < map1.sourceRangeBound) // no overlap
                throw new IllegalStateException("overlap in source ranges");
        }
    }

    long apply(long current) {
        OptionalLong rv = OptionalLong.empty();
        for (CategoryMap map: this) {
            OptionalLong newValue = map.map(current);
            assert rv.isEmpty() || newValue.isEmpty();
            if (rv.isEmpty())
                rv = newValue;
        }
        return rv.orElse(current);
    }

}
