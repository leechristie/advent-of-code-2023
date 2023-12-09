// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package main

import (
	"fmt"
	"os"
	"strconv"
)

func part1ForLine(line string) int {
	var firstDigit rune = -1
	var lastDigit rune = -1
	for _, char := range line {
		if char >= '0' && char <= '9' {
			println(char, string(char))
			lastDigit = char
			if firstDigit == -1 {
				firstDigit = char
			}
		}
	}
	rv, _ := strconv.Atoi(string(firstDigit) + string(lastDigit))
	return rv
}

func Solve01() {

	fmt.Println("Hello, Advent of Code 2023!")
	fmt.Println("Day 1")
	lines, err := ReadInputLines(1)
	if err != nil {
		fmt.Println("Unable to open input file.")
		os.Exit(1)
	}

	var answer1 = 0
	for _, line := range lines {
		answer1 += part1ForLine(line)
	}

	fmt.Println("Part 1:", answer1)

	fmt.Println("Part 2: TODO")

}
