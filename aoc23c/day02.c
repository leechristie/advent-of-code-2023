// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "days.h"
#include "puzzle.h"

// used by string buffer, longest word is "green"
#define MAX_WORD_SIZE (5)

// longest game id of rounds
#define MAX_ROUNDS (6)

// a single color red, green, or blue
typedef enum { RED, GREEN, BLUE } Color;
static bool parse_color(char *, Color *);
//static void print_color(Color);

// a mapping of {Color -> int} used to represent a game round
typedef struct {
    int red;
    int green;
    int blue;
} CubeCounter;
//static void print_cubes(const CubeCounter *);
static void set_color(CubeCounter *, Color, int);
static void clear_colors(CubeCounter *);
static int cube_power(CubeCounter *);

// a game consisting of a game id and a list of rounds
typedef struct {
    int id;
    int round_count;
    CubeCounter rounds[MAX_ROUNDS];
} Game;
static bool read_game_header(FILE * file, Game * game);
static bool read_game(FILE *, Game *);
//static void print_game(Game *);

static bool can_play_game(Game *, const CubeCounter *);
static bool can_play_round(CubeCounter *, const CubeCounter *);
static CubeCounter fewest_cubes_for_game(Game *);
static void update_fewest_cubes_for_round(CubeCounter *, CubeCounter *);

void solve02(void) {

    FILE * file = open_input_file(2);
    Game game;

    const CubeCounter LIMITS = {.red=12, .green=13, .blue=14};

    int answer1 = 0;
    int answer2 = 0;

    // loop while the file contains more games
    while (read_game(file, &game)) {

        // Part 1: sum of IDs of games which can be played
        if (can_play_game(&game, &LIMITS))
            answer1 += game.id;
        assert(answer1 >= 0);

        // Part 2: sum of cube powers of fewest cubes needed for game
        CubeCounter fewest = fewest_cubes_for_game(&game);
        answer2 += cube_power(& fewest);
        assert(answer2 >= 0);

    }

    assert(getc(file) == EOF);
    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 2\n");
    printf("Part 1: %d\n", answer1);
    assert(2283 == answer1);
    printf("Part 2: %d\n", answer2);
    assert(78669 == answer1);

}

static bool parse_color(char * s, Color * color) {
    if (strcmp(s, "red") == 0)
        *color = RED;
    else if (strcmp(s, "green") == 0)
        *color = GREEN;
    else if (strcmp(s, "blue") == 0)
        *color = BLUE;
    else
        return false;
    return true;
}

static bool read_game_header(FILE * file, Game * game) {
    if (!ignore_string(file, "Game "))
        return false;
    char buffer[MAX_WORD_SIZE + 1];
    if (!read_string_until(file, ':', buffer, MAX_WORD_SIZE))
        die("read_string_until failed");
    game->id = parse_int(buffer);
    ignore_char(file, ' ');
    return true;
}

static bool read_game(FILE * file, Game * game) {

    if (!read_game_header(file, game))
        return false;

    char buffer[MAX_WORD_SIZE + 1];
    int count;
    char found_delimiter;
    Color color;
    CubeCounter cubes = {0};
    game->round_count = 0;

    // read the rounds
    while (true) {

        // read color count and color delimiter one of {',', ';', '\n'}
        if (!read_string_until(file, ' ', buffer, MAX_WORD_SIZE))
            die("read_string_until_any failed");
        count = parse_int(buffer);
        if (!read_string_until_any(file, ",;\n", buffer, MAX_WORD_SIZE, &found_delimiter))
            die("read_string_until_any failed");
        if (!parse_color(buffer, &color))
            die("unable to parse color");
        set_color(&cubes, color, count);

        // ',' means end of color (same round)
        // ';' means end of color and round (same game)
        // '\n' means end of color, round, and game
        if (found_delimiter == ';' || found_delimiter == '\n') {
            if (game->round_count >= MAX_ROUNDS)
                die("hit MAX_ROUNDS limit");
            game->rounds[game->round_count] = cubes;
            game->round_count++;
            clear_colors(&cubes);
        }
        if (found_delimiter == '\n')
            return true;

        // ',' and ';' are followed by a space
        ignore_char(file, ' ');

    }

}

//static void print_game(Game * game) {
//    printf("Game\n");
//    printf("----\n");
//    printf("id = %d\n", game->id);
//    printf("round_count = %d\n", game->round_count);
//    if (game->round_count < 0 || game-> round_count > MAX_ROUNDS)
//        die("invalid id of rounds");
//    for (int i = 0; i < game->round_count; i++) {
//        printf("%d: ", i);
//        print_cubes(&game->rounds[i]);
//        printf("\n");
//    }
//}

static void set_color(CubeCounter * cubes, Color color, int count) {
    switch (color) {
        case RED:
            cubes->red = count;
            break;
        case GREEN:
            cubes->green = count;
            break;
        case BLUE:
            cubes->blue = count;
            break;
        default:
            die("invalid color");
    }
}

static void clear_colors(CubeCounter * cubes) {
    cubes->red = 0;
    cubes->green = 0;
    cubes->blue = 0;
}

//static void print_color(Color color) {
//    switch (color) {
//        case RED:
//            printf("Color.RED");
//            break;
//        case GREEN:
//            printf("Color.GREEN");
//            break;
//        case BLUE:
//            printf("Color.BLUE");
//            break;
//        default:
//            die("invalid color");
//    }
//}

//static void print_cubes(const CubeCounter * cubes) {
//    printf("CubeCounter(red=%d, green=%d, blue=%d)",
//           cubes->red, cubes->green, cubes->blue);
//}

static bool can_play_game(Game * game, const CubeCounter * limits) {
    for (int i = 0; i < game->round_count; i++)
        if (!can_play_round(&game->rounds[i], limits))
            return false;
    return true;
}

static bool can_play_round(CubeCounter * round, const CubeCounter * limit) {
    if (round->red > limit->red)
        return false;
    if (round->green > limit->green)
        return false;
    if (round->blue > limit->blue)
        return false;
    return true;
}

static CubeCounter fewest_cubes_for_game(Game * game) {
    CubeCounter rv = {0, 0, 0};
    for (int i = 0; i < game->round_count; i++)
        update_fewest_cubes_for_round(&game->rounds[i], &rv);
    return rv;
}

static void update_fewest_cubes_for_round(CubeCounter * round, CubeCounter * fewest) {
    if (round->red > fewest->red)
        fewest->red = round->red;
    if (round->green > fewest->green)
        fewest->green = round->green;
    if (round->blue > fewest->blue)
        fewest->blue = round->blue;
}

static int cube_power(CubeCounter * cubes) {
    return cubes->red * cubes->green * cubes->blue;
}
