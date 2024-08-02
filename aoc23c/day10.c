// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "days.h"
#include "old_puzzletools.h"
#include "old_errortools.h"
#include "old_filetools.h"
#include "old_matrix.h"

typedef struct {
    char symbol;
} PipeSection;

static void create_pipes_matrix(OldMatrix *, OldAbsolute2D *);

void solve10(void) {

    printf("Advent of Code 2023\n");
    printf("Day 10\n");

    // read the grid of pipes from the input file
    OldMatrix pipes;
    OldAbsolute2D start;
    create_pipes_matrix(&pipes, &start);

    // print out the grid, dimensions, and start position - TESTING
    OldAbsolute2D position;
    for (position.y = 0; (size_t) position.y < pipes.dimensions.height; position.y++) {
        for (position.x = 0; (size_t) position.x < pipes.dimensions.width; position.x++) {
            PipeSection pipe_section;
            old_matrix_get(&pipes, position, &pipe_section);
            printf("%c", pipe_section.symbol);
        }
        printf("\n");
    }
    printf("dimensions = ");
    old_dimensions_print(pipes.dimensions);
    printf("\n");
    printf("start = ");
    old_absolute_2d_print(start);
    printf("\n");

    // clean up
    old_matrix_destroy(&pipes);

//    int answer1 = 0;
//    printf("Part 1: %ld\n", answer1);
//    assert(6725 == answer1);
//
//    int answer2 = 0;
//    printf("Part 2: %ld\n", answer2);
//    assert(383 == answer2);

}

static OldDimensions read_dimensions(FILE * file) {
    OldDimensions rv;
    rv.width = 0;
    rv.height = 0;
    size_t current_line_length;
    while (old_chars_until(file, '\n', &current_line_length)) {
        rv.height++;
        if (rv.width && current_line_length != rv.width)
            old_die("unequal line lengths");
        rv.width = current_line_length;
    }
    return rv;
}

static void pipe_section_create(PipeSection *, char);

static void create_pipes_matrix(OldMatrix * pipes, OldAbsolute2D * start) {
    bool set_start = false;
    FILE * file = old_open_input_file(10);
    OldDimensions dimensions = read_dimensions(file);
    fseek(file, 0, SEEK_SET);
    old_matrix_create(pipes, sizeof(PipeSection), dimensions);
    int character;
    OldAbsolute2D position;
    position.x = 0;
    position.y = 0;
    while ((character = getc(file)) != EOF) {
        char c = (char) character;
        if ((size_t) position.x == (*pipes).dimensions.width) {
            if (c != '\n')
                old_die("expected new line char");
            position.x = 0;
            position.y++;
        } else {
            if (c == '\n')
                old_die("unexpected new line char");
            if ((size_t) position.y >= (*pipes).dimensions.height)
                old_die("expected fewer lines");
            if (c == 'S') {
                if (set_start)
                    old_die("found more than one start character");
                (*start) = position;
                set_start = true;
            }
            PipeSection section;
            pipe_section_create(&section, c);
            old_matrix_set(pipes, position, &section);
            position.x++;
        }
    }
    if (position.x != 0)
        old_die("expected ending new line char");
    if ((size_t) position.y != (*pipes).dimensions.height)
        old_die("expected more lines");
    if (!set_start)
        old_die("did not set start symbol");
    fclose(file);
}

static void pipe_section_create(PipeSection * pipe_section, char symbol) {
    if (symbol != '.' && symbol != '|' && symbol != '-'
            && symbol != 'F' && symbol != '7' && symbol != 'J' && symbol != 'L'
            && symbol != 'S')
        old_die("invalid pipe symbol");
    pipe_section->symbol = symbol;
}
