// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

const day8 = require('./day08');
const day9 = require('./day09');
const day11 = require('./day11');

if (process.argv.length !== 3) {
    throw new TypeError('Valid day not specified in command line argument.')
}
let day = parseInt(process.argv[2]);
if (day === 8) {
    day8();
} else if (day === 9) {
    day9();
} else if (day === 11) {
    day11();
} else {
    throw new TypeError('Valid day not specified in command line argument.')
}
