// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

const assert = require("assert");
const fs = require("fs");

function inputString(day) {
    const day2digits = day < 10 ? `0${day}` : `${day}`;
    const path = `../input/input${day2digits}.txt`;
    return fs.readFileSync(path, 'utf-8');
}

function inputLines(day) {
    const input = inputString(day);
    let rv = input.split('\n');
    // strip training line break
    while (rv[rv.length - 1].length === 0)
        rv = rv.slice(0, rv.length - 1);
    return rv;
}

function _gcd(a, b) {
    if (a === 0)
        return b;
    if (b === 0)
        return a;
    return _gcd(b, a % b);
}

function gcd(a, b) {
    assert.strictEqual(a > 0 && b > 0, true);
    return _gcd(a, b);
}

function _lcm(a, b) {
    assert.strictEqual(a > 0 && b > 0, true);
    return (a * b) / gcd(a, b);
}

function lcm(values) {
    let rv = 1;
    values.forEach((value) => {
        rv = _lcm(rv, value);
    });
    return rv;
}

function sum(values) {
    return values.reduce((a, b) => a + b, 0);
}

function split(string, delimiter, dtype) {
    return string.split(delimiter).map(dtype);
}

module.exports = {
    inputLines,
    lcm,
    sum,
    split
};
