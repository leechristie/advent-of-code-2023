// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package aoc23java;

import java.io.*;

public final class Main {

    private Main() {
        throw new AssertionError();
    }

    public static void main(String[] args) throws IOException {
        String arg = args.length >= 1 ? args[args.length - 1] : "";
        switch (arg) {
            case "1":
                Day01.solve();
                break;
            case "2":
                Day02.solve();
                break;
            case "5":
                Day05.solve();
                break;
            default:
                System.out.println("Valid day not specified in command line argument.");
                System.exit(1);
        }
    }

}
