// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <iostream>
#include <array>
#include "days.hpp"
#include "puzzle.hpp"

static constexpr std::size_t NUM_COLORS = 3;
static constexpr std::array<std::string, NUM_COLORS> COLOR_NAMES{"red", "green", "blue"};
typedef std::array<int, NUM_COLORS> color_array;

static constexpr color_array AVAILABLE_CUBES = color_array{12, 13, 14};

class Cubes {
public:
    explicit Cubes(color_array c) {
        this->colors = c;
    }
    color_array get_colors() {
        return colors;
    }
    bool can_play() {
        for (std::size_t i = 0; i < NUM_COLORS; i++)
            if (AVAILABLE_CUBES[i] < colors[i])
                return false;
        return true;
    }
    static void parse_cube_count(color_array &arr, const std::string s) {
        for (color_array::size_type i = 0; i < arr.size(); i++) {
            const std::string& color = COLOR_NAMES[i];
            std::string::size_type pos = s.find(color);
            if (pos != std::string::npos)
                arr[i] = std::stoi(s.substr(0, pos - 1));
        }
    }
    static Cubes parse(const std::string& line) {
        color_array colors{};
        std::string::size_type lower = -1;
        std::string::size_type bound;
        while ((bound = line.find(',', lower + 1)) != std::string::npos) {
            parse_cube_count(colors, line.substr(lower + 1, bound - (lower + 1)));
            lower = bound + 1;
        }
        parse_cube_count(colors, line.substr(lower + 1));
        return Cubes(colors);
    }
    int power() {
        int rv = 1;
        for (auto &count : colors)
            rv *= count;
        return rv;
    }
private:
    color_array colors;
};

class Game {
public:
    explicit Game(int n, std::vector<Cubes> c) {
        game_number = n;
        cubes = std::move(c);
    }
    [[nodiscard]] int get_game_number() const {
        return game_number;
    }
    std::vector<Cubes> get_cubes() {
        return cubes;
    }
    static Game parse(const std::string& line) {

        // parse the game number
        const std::string::size_type numLower = line.find(' ') + 1;
        const std::string::size_type numBound = line.find(':');
        const int num = std::stoi(line.substr(numLower, numBound-numLower));

        // parse the game rounds
        std::vector<Cubes> cubes{};
        std::string::size_type lower = numBound;
        std::string::size_type bound;
        while ((bound = line.find(';', lower + 1)) != std::string::npos) {
            cubes.push_back(Cubes::parse(line.substr(lower + 2, bound - (lower + 2))));
            lower = bound;
        }
        cubes.push_back(Cubes::parse(line.substr(lower + 2)));

        return Game{num, cubes};

    }
    bool can_play() {
        for (auto &c: this->get_cubes()) {
            if (!c.can_play()) {
                return false;
            }
        }
        return true;
    }
    static void update_minimum_cubes(color_array &minimum, const color_array &c) {
        for (color_array::size_type i = 0; i < NUM_COLORS; i++) {
            if (c[i] > minimum[i]) {
                minimum[i] = c[i];
            }
        }
    }
    Cubes minimum_cubes() {
        color_array rv{};
        for (auto &c: this->get_cubes()) {
            update_minimum_cubes(rv, c.get_colors());
        }
        return Cubes(rv);
    }
private:
    int game_number;
    std::vector<Cubes> cubes;
};

std::ostream &operator<<(std::ostream &os, Cubes cube) {
    color_array colors = cube.get_colors();
    return os << "Cubes(" << COLOR_NAMES[0] << '=' << colors[0] << ", "
                          << COLOR_NAMES[1] << '=' << colors[1] << ", "
                          << COLOR_NAMES[2] << '=' << colors[2] << ")";
}

std::ostream &operator<<(std::ostream &os, const std::vector<Cubes>& cubes) {
    os << '[';
    bool first = true;
    for (auto &cube : cubes) {
        if (!first)
            os << ", ";
        os << cube;
        first = false;
    }
    return os << ']';
}

std::ostream &operator<<(std::ostream &os, Game g) {
    return os << "Game(game_number=" << g.get_game_number() << ", cubes=" << g.get_cubes() << ")";
}

void solve02() {

    std::cout << "Advent of Code 2023" << std::endl;
    std::cout << "Day 2" << std::endl;

    int answer1 = 0;
    int answer2 = 0;
    for (auto &line : get_puzzle_lines(2)) {
        Game game = Game::parse(line);
        //std::cout << game << '\n';
        if (game.can_play()) {
            answer1 += game.get_game_number();
        }
        answer2 += game.minimum_cubes().power();
    }

    std::cout << "Part 1: " << answer1 << std::endl;
    std::cout << "Part 2: " << answer2 << std::endl;

}
