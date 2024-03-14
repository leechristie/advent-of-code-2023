// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

pub fn solve() {

    println!("Advent of Code 2023");
    println!("Day 1");

    let mut answer1: u32 = 0;
    input_lines(|line| answer1 += get_calibration_value(line));
    println!("Part 1: {answer1}");
    assert_eq!(54708, answer1);

    println!("Part 2: TODO");

}

fn input_lines<F>(f: F) where F: FnMut(&str) {
    std::fs::read_to_string("../input/input01.txt")
        .expect("unable to read input file")
        .lines()
        .for_each(f);
}

fn get_calibration_value(line: &str) -> u32 {

    let mut first: Option<u32> = None;
    let mut last: Option<u32> = None;

    for c in line.chars() {
        let current = c.to_digit(10);
        if current.is_some() {
            if first.is_none() {
                first = current;
            }
            last = current;
        }
    }

    let first = first.expect("missing first digit");
    let last = last.expect("missing last digit");

    return first * 10 + last;

}
