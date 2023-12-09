// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package main

import (
	"io"
	"os"
	"strconv"
	"strings"
)

func OpenInputFile(day int) (*os.File, func(), error) {
	var dayStr = strconv.Itoa(day)
	if day < 10 {
		dayStr = "0" + dayStr
	}
	var filename = "/Users/0x1ac/Developer/leechristie/advent-of-code-2023/input/input" + dayStr + ".txt"
	file, err := os.Open(filename)
	if err != nil {
		return nil, nil, err
	}
	var closer = func() {
		file.Close()
	}
	return file, closer, nil
}

func ReadInputFile(day int) (string, error) {
	file, closer, err := OpenInputFile(1)
	if err != nil {
		return "", err
	}
	defer closer()
	reader := io.Reader(file)
	data, err := io.ReadAll(reader)
	if err != nil {
		return "", err
	}
	return string(data), nil
}

func ReadInputLines(day int) ([]string, error) {
	lines, err := ReadInputFile(1)
	if err != nil {
		return nil, err
	}
	return strings.Split(lines, "\n"), nil
}
