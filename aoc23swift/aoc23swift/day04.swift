// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

import Foundation

private struct Card {

    let number: Int
    let chosen: [Int]
    let drawn: [Int]
    let matches: Int
    let score: Int

    init(fromInputLine line: Substring) throws {
        let split1 = line.split(separator: ":")
        if (split1.count != 2) {
            throw InputError.UnableToParseLine
        }
        let token1 = String(split1[0])
        let token2 = String(split1[1])
        let split2 = token1.split(separator: " ")
        if (split2.count != 2) {
            throw InputError.UnableToParseLine
        }
        let number = Int(split2[1])!
        let split3 = token2.split(separator: "|")
        if (split3.count != 2) {
            throw InputError.UnableToParseLine
        }
        let token3 = String(split3[0])
        let token4 = String(split3[1])
        var chosen = [Int]()
        for c in token3.split(separator: " ") {
            chosen.append(Int(c)!)
        }
        var drawn = [Int]()
        var matches = 0
        var score = 0
        for d in token4.split(separator: " ") {
            let d = Int(d)!
            drawn.append(d)
            if chosen.contains(d) {
                matches += 1
                if (score == 0) {
                    score = 1
                } else {
                    score *= 2
                }
            }
        }
        self.number = number
        self.chosen = chosen
        self.drawn = drawn
        self.matches = matches
        self.score = score
    }

}

func solve04() throws {

    print("Advent of Code 2023")
    print("Day 4")

    let contents = readInput(day: 4)

    var copies: [Int:Int] = [:]
    var cards: [Int:Card] = [:]

    var total = 0
    var numCards = 0
    for line in contents.split(separator: "\n") {
        let card = try Card(fromInputLine: line)
        total += card.score
        copies[card.number] = 1
        cards[card.number] = card
        if (card.number != numCards + 1) {
            throw InputError.UnableToParseLine
        }
        numCards += 1
    }
    print("Part 1: \(total)")

    var numScratched = 0
    for cardNumber in 1...numCards {
        let copiesOfCurrent = copies[cardNumber]!
        numScratched += copiesOfCurrent
        let card = cards[cardNumber]!
        let matches = card.matches
        if (matches > 0) {
            for wonCardNumber in (cardNumber + 1)...(cardNumber + matches) {
                if (wonCardNumber <= numCards) {
                    copies[wonCardNumber] = copies[wonCardNumber]! + copiesOfCurrent
                }
            }
        }
    }
    print("Part 2: \(numScratched)")

}
