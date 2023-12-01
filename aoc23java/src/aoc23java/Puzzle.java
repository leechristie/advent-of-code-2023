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

    public static BufferedReader inputLines(int day) throws FileNotFoundException {
        String dayString = (day < 10 ? "0" : "") + day;
        File file = new File(INPUT_PATH + "input" + dayString + ".txt");
        return new BufferedReader(new FileReader(file));
    }

}
