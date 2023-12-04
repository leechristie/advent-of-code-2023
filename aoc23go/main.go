// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

package main

import (
	"fmt"
	"os"
)

func main() {

	var args = os.Args[1:]
	var arg string
	if len(args) == 1 {
		arg = args[0]
	}

	switch arg {
	case "1":
		Solve01()
	default:
		fmt.Println("Valid day not specified in command line argument.")
	}

}
