# Logbook

## Introduction

### The Challenge

Last year, my first Advent of Code, I solved each daily puzzle using Python on the same day of its release (except for Day 19 Part 2), getting all 50 stars by Christmas day. My solutions and rankings are in [my AoC 2022 GitHub repo](https://github.com/leechristie/advent-of-code-2022).

For 2023, I decided not to aim to finish each puzzle on the day. Instead, I aim to complete all puzzles in 8 different programming languages. This will of course take me long into 2024 if I finish at all. I have chosen a mixture of languages I am very familiar with (**Java**, **Python**), sort-of familiar with (**C**, **JavaScript**, **Swift**), and new to (**C++**, **Go**, **Rust**) for broad coding practice.

Solutions across different languages will be written separately making use of the typical programming paradigms of each language as far as I am able, not just line-by-line transliterations. Each language will have its own project that covers all 25 puzzles, rather than writing 25 projects per language. This is so I can build up a set of reusable functions and classes for each language as I go. If possible, I want to write an option so I can run that language's solvers for each puzzle in turn and time each.

I will write all code from scratch with no LLMs or spoilers. I am also avoiding third-party code beyond the each language's built-in standard library.  For JavaScript I can't really use the standard library that comes with a browser, so I'm going with the NodeJS built-in modules as the standard library for back-end applications, such as `fs` to load the puzzle input file from disk, but I won't be downloading `npm` packages.

My approach to AoC 2022 in Python sparingly used a couple of third-party libraries like `numpy`, `sympy`, `re`, and `tqdm`. While there is value in learning the landscape of third-party packages, I think it's more fun to spend this challenge hand-rolling algorithms and data structures, not googling random packages.

### Languages and Editors

For my own future reference, I have noted down the versions I used. All compilers / interpreters are the native Apple Silicon builds for macOS. For most languages, I am targeting the latest language version, except C and C++ because of the virtual impossibility of finding compiler support. Maybe I'll change my mind later and hunt for a more up-to-date compiler. I may not always use all relevant recent features of these versions, especially with unfamiliar languages.

I use the [JetBrains All Products Pack](https://www.jetbrains.com/all/) for my IDEs of choice for consistent developer UX. Xcode would be better for Swift and AppCode is EOL, but I'm not likely to use the UI builder or simulators and want to simplify the editor choice.

| Language   | Version | Compiler/Interpreter                | IDE                                       |
|:-----------|:--------|:------------------------------------|:------------------------------------------|
| C          | C17     | GCC 13.2.0 (Homebrew)†              | CLion 2023.2.2                            |
| C++        | C++17   | GCC 13.2.0 (Homebrew)†              | CLion 2023.2.2                            |
| Go         | 1.20    | Go 1.21.4                           | GoLand 2023.2.4                           |
| Java       | 21      | 21.0.1+12 LTS (Azul Zulu Community) | IntelliJ IDEA 2023.2.5 (Ultimate Edition) |
| JavaScript | ES2021  | Node.js 21.1.0†                     | WebStorm 2023.2.4                         |
| Python     | 3.12    | Python 3.12.0, (Mambaforge 1.5.3)   | PyCharm 2023.2.5 (Professional Edition)   |
| Rust       | 2021    | Rust 1.73.0                         | RustRover 2023.3 EAP                      |
| Swift      | 5.9     | Apple Clang 15.0.0†                 | AppCode 2023.1.4†                         |

† May not provide full support for all features of the target language version

### Reminders

Homebrew GCC installs as `gcc-13`/`g++-13`.

To set flags on C/C++ compiler in Clion, since this is difficult to find:

**Settings** > **Build, Execution, Deployment** > **CMake** > **CMake Options**
```
-DCMAKE_C_FLAGS="-Wall -Wextra -Wpedantic -Werror"
-DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic -Werror"
```
