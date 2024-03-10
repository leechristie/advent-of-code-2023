// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java.day08;

import aoc23java.Puzzle;

import java.io.*;
import java.util.*;

public class Day08 {

    private Day08() {
        throw new AssertionError();
    }

    private record OutEdges(String left, String right) {}
    private record Input(String header, Map<String, OutEdges> body) {}

    public static void solve() {

        System.out.println("Advent of Code 2023");
        System.out.println("Day 8");

        Input input = readInput();
        Set<String> ghostStartNodes = nodesEnding(input, 'A');
        Set<String> ghostEndNodes = nodesEnding(input, 'Z');
        Map<String, Long> ghostPeriods = followGhosts(input, ghostStartNodes, ghostEndNodes);

        long answer1 = ghostPeriods.get("AAA");
        System.out.println("Part 1: " + answer1);
        assert 12169L == answer1;

        long answer2 = Puzzle.lcm(ghostPeriods.values());
        System.out.println("Part 2: " + answer2);
        assert 12030780859469L == answer2;

    }

    private static Map<String, Long> followGhosts(Input input,
                                                  Set<String> ghostStartNodes,
                                                  Set<String> ghostEndNodes) {
        Map<String, Long> rv = new HashMap<>();
        for (String ghostStart: ghostStartNodes) {
            String ghostCurrent = ghostStart;
            long steps = 0;
            for (char nextDirection : Puzzle.repeat(input.header)) {
                if (nextDirection == 'L') {
                    ghostCurrent = input.body().get(ghostCurrent).left();
                } else {
                    assert nextDirection == 'R';
                    ghostCurrent = input.body().get(ghostCurrent).right();
                }
                steps++;
                if (ghostEndNodes.contains(ghostCurrent)) {
                    rv.put(ghostStart, steps);
                    break;
                }
            }
        }
        return rv;
    }

    private static Set<String> nodesEnding(Input input, char character) {
        Set<String> rv = new HashSet<>();
        for (String s: input.body().keySet())
            if (s.endsWith("" + character))
                rv.add(s);
        return rv;
    }

    private static String readHeader(BufferedReader in) throws IOException {
        String rv = in.readLine();
        assert "".equals(in.readLine());
        return rv;
    }

    private static Map<String, OutEdges> readBody(BufferedReader in) throws IOException {
        Map<String, OutEdges> rv = new HashMap<>();
        String line;
        while ((line = in.readLine()) != null) {
            String[] lhsRhs = line.split(" = ");
            assert lhsRhs.length == 2;
            String lhs = lhsRhs[0];
            assert lhs.length() == 3;
            String[] rhs = lhsRhs[1].replace("(", "")
                                    .replace(")", "")
                                    .split(", ");
            assert rhs.length == 2;
            String left = rhs[0];
            assert left.length() == 3;
            String right = rhs[1];
            assert right.length() == 3;
            assert !rv.containsKey(lhs);
            rv.put(lhs, new OutEdges(left, right));
        }
        return rv;
    }

    private static Input readInput() {
        try (BufferedReader in = Puzzle.inputLines(8, false)) {
            String header = readHeader(in);
            Map<String, OutEdges> body = readBody(in);
            return new Input(header, body);
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

}
