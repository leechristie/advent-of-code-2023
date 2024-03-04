// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

const assert = require("assert");
const puzzle = require("./puzzle");

function read_stars(example) {

    const input = puzzle.inputLines(11, example);
    var width = 0;
    var height = 0;
    var y = 0;
    var stars = [];
    input.forEach((line) => {
        var x = 0;
        line.split("").forEach((char) => {
            if (char === "#") {
                stars.push([x, y]);
            }
            x++;
            if (x > width)
                width = x;
        });
        y++;
        if (y > height)
            height = y;
    });

    return [width, height, stars];

}

function find_empty(width, height, stars) {

    var empty_xs = new Set();
    for (var x = 0; x < width; x++)
        empty_xs.add(x);

    var empty_ys = new Set();
    for (var y = 0; y < width; y++)
        empty_ys.add(y);

    stars.forEach(([x, y]) => {
        empty_xs.delete(x);
        empty_ys.delete(y);
    });
    return [empty_xs, empty_ys];

}

function count_smaller(value, others) {
    var rv = 0;
    others.forEach((other) => {
        if (other < value)
            rv++;
    });
    return rv;
}

function calculate_shift(dimension, empty) {
    var rv = new Map();
    for (var i = 0; i < dimension; i++)
        rv[i] = count_smaller(i, empty);
    return rv;
}

function apply_shift(stars, x_shift, y_shift, multiplier) {
    let added = multiplier - 1;
    var rv = [];
    stars.forEach(([x, y]) => {
        rv.push([x + added * x_shift[x], y + added * y_shift[y]]);
    });
    return rv;
}

function manhattan_distance(from, to) {
    let [x0, y0] = from;
    let [x1, y1] = to;
    return Math.abs(x0 - x1) + Math.abs(y0 - y1);
}

function calc_total_distance(stars) {
    var rv = 0;
    for (var i = 0; i < stars.length - 1; i++) {
        for (var j = i + 1; j < stars.length; j++) {
            rv += manhattan_distance(stars[i], stars[j]);
        }
    }
    return rv;
}

function solve() {

    console.log("Advent of Code 2023");
    console.log('Day 11');

    // read the stars from the file
    let [width, height, stars] = read_stars(false);

    // find the empty rows and columns
    let [empty_xs, empty_ys] = find_empty(width, height, stars);

    // calculate how much to shift the stars by
    let x_shift = calculate_shift(width, empty_xs);
    let y_shift = calculate_shift(width, empty_ys);

    // shift the stars with multiplier x2 and calculate total distance
    let moved_stars_2 = apply_shift(stars, x_shift, y_shift, 2);
    let total_distance_2 = calc_total_distance(moved_stars_2);

    console.log(`Part 1: ${total_distance_2}`);
    assert(9543156 === total_distance_2);

    // shift the stars with multiplier x1000000 and calculate total distance
    let moved_stars_1000000 = apply_shift(stars, x_shift, y_shift, 1000000);
    let total_distance_1000000 = calc_total_distance(moved_stars_1000000);

    console.log(`Part 2: ${total_distance_1000000}`);
    assert(625243292686 === total_distance_1000000);

}

module.exports = solve;
