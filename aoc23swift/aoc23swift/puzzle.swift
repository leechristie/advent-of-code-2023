//
// Created by Lee Christie on 2023-12-07.
//

import Foundation

enum InputError: Error {
    case UnableToParseLine
}

func readInput(day: Int, example: Bool = false) -> String {
    if (day < 1 || day > 25) {
        print("Unable to open input file.")
        exit(1)
    }
    let dayFormat = String(format: "%02d", day)
    let filename = "/Users/0x1ac/Developer/leechristie/advent-of-code-2023/input/"
    let prefix = example ? "example" : "input"
    let fullPath = "\(filename)\(prefix)\(dayFormat).txt"
    let rv = try? String(contentsOfFile: fullPath)
    guard let rv else {
        print("Unable to open input file.")
        exit(1)
    }
    return rv
}
