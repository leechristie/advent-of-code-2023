// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

import Foundation

private func read_stars(example: Bool) throws -> (Int, Int, [(Int, Int)]) {
    let input = readInput(day: 11, example: example)
    var stars: [(Int, Int)] = []
    var width = 0
    var height = 0
    for (y, line) in input.split(separator: "\n").enumerated() {
        for (x, char) in line.enumerated() {
            if char == "#" {
                stars.append((x, y))
            }
            if x >= width {
                width = x + 1
            }
        }
        if y >= height {
            height = y + 1
        }
    }
    return (width, height, stars)
}

private func find_empty(width: Int, height: Int, stars: [(Int, Int)]) -> (Set<Int>, Set<Int>) {
    var empty_xs: Set<Int> = Set<Int>(0..<width)
    var empty_ys: Set<Int> = Set<Int>(0..<height)
    for (x, y) in stars {
        empty_xs.remove(x)
        empty_ys.remove(y)
    }
    return (empty_xs, empty_ys)
}

private func count_smaller(value: Int, others: Set<Int>) -> Int {
    var rv = 0
    for other in others {
        if other < value {
            rv += 1
        }
    }
    return rv
}

private func calculate_shift(dimension: Int, empty: Set<Int>) -> [Int:Int] {
    var rv: [Int:Int] = [:]
    for x in 0..<dimension {
        rv[x] = count_smaller(value: x, others: empty)
    }
    return rv
}

private func apply_shift(stars: [(Int, Int)], x_shift: [Int:Int], y_shift: [Int:Int], multiplier: Int) -> [(Int, Int)] {
    let added = multiplier - 1;
    var rv: [(Int, Int)] = []
    for (x, y) in stars {
        rv.append((x + added * x_shift[x]!, y + added * y_shift[y]!))
    }
    return rv
}

private func manhattan_distance(from: (Int, Int), to: (Int, Int)) -> Int {
    let (x0, y0) = from
    let (x1, y1) = to
    return abs(x0 - x1) + abs(y0 - y1)
}

private func calc_total_distance(stars: [(Int, Int)]) -> Int {
    var rv = 0
    for i in 0 ..< stars.count-1 {
        for j in i+1 ..< stars.count {
            rv += manhattan_distance(from: stars[i], to: stars[j])
        }
    }
    return rv
}

func solve11() throws {
    
    print("Advent of Code 2023")
    print("Day 11")
    
    // read the stars from the file
    let (width, height, stars) = try read_stars(example: false)
    
    // find the empty rows and columns
    let (empty_xs, empty_ys) = find_empty(width: width, height: height, stars: stars)
    
    // calculate how much to shift the stars by
    let x_shift = calculate_shift(dimension: width, empty: empty_xs)
    let y_shift = calculate_shift(dimension: height, empty: empty_ys)
    
    // shift the stars with multiplier x2 and calculate total distance
    let moved_stars_2 = apply_shift(stars: stars, x_shift: x_shift, y_shift: y_shift, multiplier: 2)
    var total_distance_2 = calc_total_distance(stars: moved_stars_2)
    
    print("Part 1: \(total_distance_2)")
    assert(9543156 == total_distance_2)
    
    // shift the stars with multiplier x1000000 and calculate total distance
    let moved_stars_1000000 = apply_shift(stars: stars, x_shift: x_shift, y_shift: y_shift, multiplier: 1000000)
    var total_distance_1000000 = calc_total_distance(stars: moved_stars_1000000)
        
    print("Part 2: \(total_distance_1000000)")
    assert(625243292686 == total_distance_1000000)
    
}
