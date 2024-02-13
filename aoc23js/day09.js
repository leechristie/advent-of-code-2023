// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

const assert = require("assert");
const puzzle = require("./puzzle");

function _extrapolate(values, bound) {
    let seen_non_zero = false;
    for (let i = 0; i <= bound - 2; i++) {
        values[i] = values[i+1] - values[i];
        if (values[i] !== 0)
            seen_non_zero = true;
    }
    if (seen_non_zero)
        _extrapolate(values, bound - 1);
}

function extrapolate(values) {
    _extrapolate(values, values.length);
    return puzzle.sum(values);
}

function solve() {

    console.log("Advent of Code 2023");
    console.log('Day 9');

    let answer1 = 0;
    let answer2 = 0;

    const input = puzzle.inputLines(9);
    input.forEach((line) => {
        let forwards = puzzle.split(line, " ", Number);
        let backwards = forwards.toReversed();
        answer1 += extrapolate(forwards);
        answer2 += extrapolate(backwards);
    });

    console.log(`Part 1: ${answer1}`);
    assert.strictEqual(answer1, 1972648895);

    console.log(`Part 2: ${answer2}`);
    assert.strictEqual(answer2, 919);

}

module.exports = solve;
