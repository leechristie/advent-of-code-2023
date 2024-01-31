// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java;

import aoc23java.day01.Day01;
import aoc23java.day02.Day02;
import aoc23java.day05.Day05;
import aoc23java.day07.Day07;
import aoc23java.day08.Day08;

import java.io.*;
import java.util.Map;
import java.util.NoSuchElementException;

public final class Main {

    private Main() {
        throw new AssertionError();
    }

    public static void main(String[] args) throws IOException {

        String arg = args.length >= 1 ? args[args.length - 1] : "";
        Map<Integer, Runnable> solvers = Map.ofEntries(Map.entry(1, Day01::solve),
                                                       Map.entry(2, Day02::solve),
                                                       Map.entry(5, Day05::solve),
                                                       Map.entry(7, Day07::solve),
                                                       Map.entry(8, Day08::solve));

        int day;
        try {
            day = Integer.parseInt(arg);
        } catch (NumberFormatException ex) {
            System.out.println("Valid day not specified in command line argument.");
            System.exit(1);
            return;
        }

        Runnable solver;
        try {
            solver = solvers.get(day);
        } catch (NoSuchElementException ex) {
            System.out.println("Valid day not specified in command line argument.");
            System.exit(1);
            return;
        }

        solver.run();

    }

}
