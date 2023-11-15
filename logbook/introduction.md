# Logbook

## Introduction

Last year, [my first Advent of Code](https://github.com/leechristie/advent-of-code-2022), I solved each daily puzzle using Python on the same day of its release (except for [Day 19](https://adventofcode.com/2022/day/19)), getting all 50 stars by Christmas day.

For 2023, I decided not to aim to finish to try to solve each day. Instead, I aim to complete all puzzles in 8 different programming languages. I have chosen a mixture of languages I am very familiar with and those I am either new to or long out-of-practice.

Solutions across different languages will be written separately, not transliterated, and attempt to make use of the typical programming paradigms of each language as far as I am able. Each language has a single solution project that covers each day, rather than writing 25 projects per language, so that I can build up a set of reusable functions as I go. All code was written from scratch with no LLMs or spoilers. I am also avoiding third-party code beyond the each language's built-in standard library, even if it means needing to hand-roll basic algorithms and data structures.

For my own future reference, I have noted down the versions I used. All compilers / interpreters are the native Apple Silicon builds for macOS. I may not always use all relevant recent features of these versions, especially with unfamiliar languages. I use the [JetBrains All Products Pack](https://www.jetbrains.com/all/) for my IDEs of choice for consistent developer UX.

| Language   | Version | Compiler/Interpreter                | IDE                                       |
|:-----------|:--------|:------------------------------------|:------------------------------------------|
| C          | C17     | Apple Clang 15.0.0†                 | CLion 2023.2.2                            |
| C++        | C++17   | Apple Clang 15.0.0†                 | CLion 2023.2.2                            |
| Go         | 1.20    | Go 1.21.4                           | GoLand 2023.2.4                           |
| Java       | 21      | 21.0.1+12 LTS (Azul Zulu Community) | IntelliJ IDEA 2023.2.5 (Ultimate Edition) |
| JavaScript | ES2021† | Node.js 21.1.0                      | WebStorm 2023.2.4                         |
| Python     | 3.12    | Python 3.12.0, (Mambaforge 1.5.3)   | PyCharm 2023.2.4 (Professional Edition)   |
| Rust       | 2021    | Rust 1.73.0                         | RustRover 2023.3 EAP                      |
| Swift      | 5.9     | Apple Clang 15.0.0†                 | AppCode 2023.1.4†                         |

† May not provide full support for all features of the target language version
