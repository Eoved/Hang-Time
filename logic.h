#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


struct game {
    unsigned int run, hangtime;
    board* b;
    posqueue* hanging;
    turn player;
};

typedef struct game game;

typedef enum dir dir;


enum dir {
    RIGHT,
    DOWN,
    UP_RIGHT,
    DOWN_RIGHT
};

//Creates a new clear game
game* new_game(unsigned int run, unsigned int hangtime, unsigned int width,
               unsigned int height, enum type type);

//Entirely frees a game
void game_free(game* g);

//Applies gravity to the board for falling for pos p
void fall(game *g, pos p);

//Places a piece at pos p and returns true, if spot is filled returns false
bool place_piece(game* g, pos p);

//Checks the length of a run from pos p
unsigned int get_run(board *b, pos p, cell color, dir d);

//Determines the current outcome of the game
outcome game_outcome(game* g);

#endif /* LOGIC_H */
