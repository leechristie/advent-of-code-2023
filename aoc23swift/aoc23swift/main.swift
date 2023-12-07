// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

if (CommandLine.arguments.count != 2) {
    print("Valid day not specified in command line argument.")
    exit(1)
}
let arg: Int? = Int(CommandLine.arguments[1])
guard let arg = arg else {
    print("Valid day not specified in command line argument.")
    exit(1)
}
switch arg {
case 4:
    solve04()
default:
    print("Valid day not specified in command line argument.")
    exit(1)
}
