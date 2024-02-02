// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

const assert = require("assert");

const puzzle = require('./puzzle')

function readInput() {
    const input = puzzle.inputLines(8);
    assert.strictEqual(input[1], '');  // blank line between header and body
    const header = input[0];
    let body = new Map();
    for (let i = 2; i < input.length; i++) {  // lines 2 to end
        const [lhs, rhs] = input[i].split(' = ');
        const [left, right] = rhs
            .replace('(', '')
            .replace(')', '')
            .split(', ');
        body.set(lhs, [left, right]);
    }
    return [header, body];
}

function solve() {

    console.log("Advent of Code 2023");
    console.log('Day 8');

    const [header, body] = readInput();

    const ghosts = [];
    const endNodes = new Set();
    body.forEach((value, key) => {
        if (key.endsWith('A'))
            ghosts.push(key);
        if (key.endsWith('Z'))
            endNodes.add(key);
    });

    const ghostPeriods = new Map();
    ghosts.forEach((ghostStart) => {
        let steps = 0;
        let ghostCurrent = ghostStart;
        for (let i = 0; true; i = (i + 1) % header.length) {
            const [left, right] = body.get(ghostCurrent);
            if (header[i] === 'L') {
                ghostCurrent = left;
            } else {
                assert.strictEqual(header[i], 'R');
                ghostCurrent = right;
            }
            steps++;
            if (endNodes.has(ghostCurrent)) {
                ghostPeriods.set(ghostStart, steps);
                break;
            }
        }
    });

    let answer1 = ghostPeriods.get('AAA');
    console.log(`Part 1: ${answer1}`);
    assert.strictEqual(answer1, 12169);

    let answer2 = puzzle.lcm([...ghostPeriods.values()]);
    console.log(`Part 2: ${answer2}`);
    assert.strictEqual(answer2, 12030780859469);

}

module.exports = solve;
