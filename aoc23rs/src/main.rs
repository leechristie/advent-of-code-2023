// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

mod day01;

fn main() {
    let invalid_arg = "Valid day not specified in command line argument.";
    let arg: String = std::env::args().last().expect(invalid_arg);
    let day = arg.parse::<i8>().expect(invalid_arg);
    match day {
        1 => day01::solve(),
        _ => panic!("{}", invalid_arg)
    }
}
