// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java;

import java.io.*;

public final class Puzzle {

    private static final String INPUT_PATH = "../input/";

    private Puzzle() {
        throw new AssertionError();
    }

    public static BufferedReader inputLines(int day) {
        return inputLines(day, false);
    }

    public static BufferedReader inputLines(int day, boolean example) {
        try {
            String dayString = (day < 10 ? "0" : "") + day;
            String prefix = example ? "example" : "input";
            File file = new File(INPUT_PATH + prefix + dayString + ".txt");
            return new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException ex) {
            throw new RuntimeException(ex);
        }
    }

}
