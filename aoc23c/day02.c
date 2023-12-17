// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "days.h"
#include "puzzle.h"

// used by string buffer, longest word is "green"
#define MAX_WORD_SIZE (5)

// a single color red, green, or blue
typedef enum { RED, GREEN, BLUE } Color;
#define NUM_COLORS (3)
bool parse_color(char *, Color *);
void print_color(Color);

// a mapping of {Color -> int} used to represent a game round
typedef struct {
    int red;
    int green;
    int blue;
} CubeCounter;
void print_cubes(CubeCounter);
void set_color(CubeCounter *, Color, int);
int get_color(CubeCounter *, Color);
void clear_colors(CubeCounter *);

// a game consisting of a game number and a list of rounds
typedef struct {
    int number;
} Game;
bool read_game(FILE *, Game *);
void print_game(Game *);

void solve02(void) {

    FILE * file = open_input_file(2);
    Game game;

    // loop while the file contains more games
    while (read_game(file, &game)) {

        print_game(&game);
        printf("\n");

    }

    assert(getc(file) == EOF);
    fclose(file);

    printf("Advent of Code 2023!\n");
    printf("Day 2\n");
    printf("Part 1: TODO\n");
    printf("Part 2: TODO\n");

}

bool parse_color(char * s, Color * color) {
    if (strcmp(s, "red") == 0) {
        *color = RED;
        return true;
    }
    if (strcmp(s, "green") == 0) {
        *color = GREEN;
        return true;
    }
    if (strcmp(s, "blue") == 0) {
        *color = BLUE;
        return true;
    }
    return false;
}

bool read_game(FILE * file, Game * game) {

    // header "Game n: "
    if (!ignore_string(file, "Game "))
        return false;
    char buffer[MAX_WORD_SIZE + 1];
    if (!read_string_until(file, ':', buffer, MAX_WORD_SIZE))
        die("read_until failed 7");
    game->number = atoi(buffer);
    ignore_char(file, ' ');

    int count;
    char found_delimiter;
    Color color;
    CubeCounter cubes = {0};

    while (true) {

        if (!read_string_until(file, ' ', buffer, MAX_WORD_SIZE))
            die("read_until failed");
        count = atoi(buffer);
        if (!read_string_until_any(file, ",;\n", buffer, MAX_WORD_SIZE, &found_delimiter))
            die("read_until failed");
        if (!parse_color(buffer, &color))
            die("unable to parse color");
        set_color(&cubes, color, count);

        if (found_delimiter == ';' || found_delimiter == '\n') {
            printf("cubes = "); print_cubes(cubes); printf("\n");
            clear_colors(&cubes);
        }
        if (found_delimiter == '\n')
            return true;

        ignore_char(file, ' ');

    }

}

void print_game(Game * game) {
    printf("Game(number=%d)\n", game->number);
}

void set_color(CubeCounter * cubes, Color color, int count) {
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

int get_color(CubeCounter * cubes, Color color) {
    switch (color) {
        case RED:
            return cubes->red;
        case GREEN:
            return cubes->green;
        case BLUE:
            return cubes->blue;
        default:
            die("invalid color");
    }
}

void clear_colors(CubeCounter * cubes) {
    cubes->red = 0;
    cubes->green = 0;
    cubes->blue = 0;
}

void print_color(Color color) {
    switch (color) {
        case RED:
            printf("Color.RED");
            break;
        case GREEN:
            printf("Color.GREEN");
            break;
        case BLUE:
            printf("Color.BLUE");
            break;
        default:
            die("invalid color");
    }
}

void print_cubes(CubeCounter cubes) {
    printf("CubeCounter(red=%d, green=%d, blue=%d)",
           cubes.red, cubes.green, cubes.blue);
}
