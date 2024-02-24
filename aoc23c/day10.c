// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "days.h"
#include "puzzletools.h"
#include "errortools.h"
#include "filetools.h"
#include "matrix.h"

typedef struct {
    char symbol;
} PipeSection;

static void create_pipes_matrix(Matrix *, Absolute2D *);

void solve10(void) {

    printf("Advent of Code 2023\n");
    printf("Day 10\n");

    // read the grid of pipes from the input file
    Matrix pipes;
    Absolute2D start;
    create_pipes_matrix(&pipes, &start);

    // print out the grid, dimensions, and start position - TESTING
    Absolute2D position;
    for (position.y = 0; (size_t) position.y < pipes.dimensions.height; position.y++) {
        for (position.x = 0; (size_t) position.x < pipes.dimensions.width; position.x++) {
            PipeSection pipe_section;
            matrix_get(&pipes, position, &pipe_section);
            printf("%c", pipe_section.symbol);
        }
        printf("\n");
    }
    printf("dimensions = ");
    dimensions_print(pipes.dimensions);
    printf("\n");
    printf("start = ");
    absolute_2d_print(start);
    printf("\n");

    // clean up
    matrix_destroy(&pipes);

//    int answer1 = 0;
//    printf("Part 1: %ld\n", answer1);
//    assert(6725 == answer1);
//
//    int answer2 = 0;
//    printf("Part 2: %ld\n", answer2);
//    assert(383 == answer2);

}

static Dimensions read_dimensions(FILE * file) {
    Dimensions rv;
    rv.width = 0;
    rv.height = 0;
    size_t current_line_length;
    while (chars_until(file, '\n', &current_line_length)) {
        rv.height++;
        if (rv.width && current_line_length != rv.width)
            die("unequal line lengths");
        rv.width = current_line_length;
    }
    return rv;
}

static void pipe_section_create(PipeSection *, char);

static void create_pipes_matrix(Matrix * pipes, Absolute2D * start) {
    bool set_start = false;
    FILE * file = open_input_file(10);
    Dimensions dimensions = read_dimensions(file);
    fseek(file, 0, SEEK_SET);
    matrix_create(pipes, sizeof(PipeSection), dimensions);
    int character;
    Absolute2D position;
    position.x = 0;
    position.y = 0;
    while ((character = getc(file)) != EOF) {
        char c = (char) character;
        if ((size_t) position.x == (*pipes).dimensions.width) {
            if (c != '\n')
                die("expected new line char");
            position.x = 0;
            position.y++;
        } else {
            if (c == '\n')
                die("unexpected new line char");
            if ((size_t) position.y >= (*pipes).dimensions.height)
                die("expected fewer lines");
            if (c == 'S') {
                if (set_start)
                    die("found more than one start character");
                (*start) = position;
                set_start = true;
            }
            PipeSection section;
            pipe_section_create(&section, c);
            matrix_set(pipes, position, &section);
            position.x++;
        }
    }
    if (position.x != 0)
        die("expected ending new line char");
    if ((size_t) position.y != (*pipes).dimensions.height)
        die("expected more lines");
    if (!set_start)
        die("did not set start symbol");
    fclose(file);
}

static void pipe_section_create(PipeSection * pipe_section, char symbol) {
    if (symbol != '.' && symbol != '|' && symbol != '-'
            && symbol != 'F' && symbol != '7' && symbol != 'J' && symbol != 'L'
            && symbol != 'S')
        die("invalid pipe symbol");
    pipe_section->symbol = symbol;
}
