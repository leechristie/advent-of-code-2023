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
    
    static NUMBERS: [&str; 9] = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    let mut answer2: u32 = 0;
    input_lines(|line| answer2 += get_new_calibration_value(line, &NUMBERS));
    println!("Part 2: {answer2}");
    assert_eq!(54087, answer2);

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
            last = current;
            if first.is_none() {
                first = current;
            }
        }
    }

    let first = first.expect("missing first digit");
    let last = last.expect("missing last digit");

    return first * 10 + last;

}

fn get_new_calibration_value(line: &str, numbers: &[&str; 9]) -> u32 {

    let mut first: Option<u32> = None;
    let mut last: Option<u32> = None;
    
    let chars: Vec<char> = line.chars().collect();
    
    for i in 0.. chars.len() {
        let mut current = chars[i].to_digit(10);
        if current.is_none() {
            current = get_spelled_numbers(&chars, i, &numbers);
        }
        if current.is_some() {
            last = current;
            if first.is_none() {
                first = current;
            }
        }
    }
    
    let first = first.expect("missing first digit");
    let last = last.expect("missing last digit");

    return first * 10 + last;
    
}

fn get_spelled_numbers(chars: &Vec<char>, start_index: usize, numbers: &[&str; 9]) -> Option<u32> {
    for (index, number) in numbers.iter().enumerate() {
        let rv = get_spelled_number(&chars, start_index, &number, index);
        if rv.is_some() {
            return rv;
        }
    }
    return None;
}

fn get_spelled_number(chars: &Vec<char>, start_index: usize, number: &str, index: usize) -> Option<u32> {
    let number_chars = number.chars();
    for (i, c) in number_chars.enumerate() {
        let offset: usize = start_index + i;
        if offset >= chars.len() {
            return None;
        }
        if c != chars[offset] {
            return None;
        }
    }
    return Some(index as u32 + 1);
}
