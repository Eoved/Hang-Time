#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "logic.h"
//Andrew DeVoe
// CMSC 152 - Project 1

//Creates a new clear game
game* new_game(unsigned int run, unsigned int hangtime, unsigned int width,
               unsigned int height, enum type type) {
	game *g = (game*)malloc(sizeof(game));
	if(g == NULL) {
		fprintf(stderr, "new_game: error - could not allocate memory\n");
        exit(1);
	} else if(run == 0) {
		fprintf(stderr, "new_game: error - run cannot be 0\n");
        exit(1);
	} else if((run > width) && (run > height)) {
		fprintf(stderr, "new_game: error - run too long\n");
        exit(1);
	}
	g->run = run;
	g->hangtime = hangtime;
	g->b = board_new(width, height, type);
	g->hanging = posqueue_new();
	g->player = BLACKS_TURN;
	return g;
}

//Entirely frees a game
void game_free(game* g) {
	board_free(g->b);
	posqueue_free(g->hanging);
	free(g);
}

//Applies gravity to the board for falling pos p
void fall(game *g, pos p) {
	if((p.r + 1) < g->b->height) {
		pos next = make_pos((p.r + 1), p.c);
		if(board_get(g->b, next) == EMPTY) {
			board_set(g->b, next, board_get(g->b, p));
			board_set(g->b, p, EMPTY);
			//Check for element above to fall
			if(p.r > 0) {
				pos prev = make_pos(p.r - 1, p.c);
				if((board_get(g->b, prev) != EMPTY) && 
				   (!posqueue_member(g->hanging, prev))) {
					fall(g, prev);
				}
			}
			fall(g, next);
		}
	}
}

//Places a piece at pos p and returns true, if spot is filled returns false
bool place_piece(game* g, pos p) {
	if((p.r > g->b->height) || (p.c > g->b->width)) {
        return false;
    } else if(board_get(g->b, p) != EMPTY) {
		return false;
	} else {
		//Sets the new piece
		if(g->player == BLACKS_TURN) {
			board_set(g->b, p, BLACK);
		} else if(g->player == WHITES_TURN) {
			board_set(g->b, p, WHITE);
		}
		
		//Applies gravity to pieces
		pos_enqueue(g->hanging, p);
		if(g->hanging->len > g->hangtime) {
			pos f = pos_dequeue(g->hanging);
			fall(g, f);
		}

		//Switches the Player
		if(g->player == BLACKS_TURN) {
			g->player = WHITES_TURN;
		} else if(g->player == WHITES_TURN) {
			g->player = BLACKS_TURN;
		}
		return true;
	}
}

//Checks the length of a run from pos p
unsigned int get_run(board *b, pos p, cell color, dir d) {
	unsigned int run = 0;
	if(d == RIGHT) {
		for(unsigned int j = p.c; j < b->width; j++) {
			if(board_get(b, make_pos(p.r, j)) == color) {
				run++;
			} else {
				break;
			}
		}
	} else if(d == DOWN) {
		for(unsigned int i = p.r; i < b->height; i++) {
			if(board_get(b, make_pos(i, p.c)) == color) {
				run++;
			} else {
				break;
			}
		}
	} else if(d == UP_RIGHT) {
		unsigned int i = p.r;
		for(unsigned int j = p.c; j < b->width; j++) {
			if(board_get(b, make_pos(i, j)) == color) {
				run++;
			} else {
				break;
			}
			if(i == 0) {
				break;
			} else {
				i--;
			}
		}
	} else if(d == DOWN_RIGHT) {
		unsigned int i = p.r;
		for(unsigned int j = p.c; j < b->width; j++) {
			if(board_get(b, make_pos(i, j)) == color) {
				run++;
			} else {
				break;
			}
			if(i == (b->height - 1)) {
				break;
			} else {
				i++;
			}
		}
	}
	return run;
}

//Determines the current outcome of the game
outcome game_outcome(game* g) {
	unsigned int len = 0;
	bool b_win = false;
	bool w_win = false;
	bool no_space = true;
	for(unsigned int i = 0; i < g->b->height; i++) {
		for(unsigned int j = 0; j < g->b->width; j++) {
			pos p = make_pos(i, j);
			cell curr = board_get(g->b, p);
			if(no_space && (curr == EMPTY)) {
				no_space = false;
			} else {
				if(((curr == BLACK) && b_win) || ((curr == WHITE) && w_win)) {
					continue;
				} else {
					//Gets the longest run from the point
					len = get_run(g->b, p, curr, RIGHT);
					unsigned int down = get_run(g->b, p, curr, DOWN);
					if(down > len) {
						len = down;
					}
					unsigned int u_right = get_run(g->b, p, curr, UP_RIGHT);
					if(u_right > len) {
						len = u_right;
					}
					unsigned int d_right = get_run(g->b, p, curr, DOWN_RIGHT);
					if(d_right > len) {
						len = d_right;
					}
				}
				//Checks if run is same or longer than min run to win
				if(len >= g->run) {
					if(curr == BLACK) {
						b_win = true;
					} else if(curr == WHITE) {
						w_win = true;
					}
				}
			}
		}
	}
	if(b_win && w_win) {
		return DRAW;
	} else if(b_win) {
		return BLACK_WIN;
	} else if(w_win) {
		return WHITE_WIN;
	} else if(no_space) {
		return DRAW;
	} else {
		return IN_PROGRESS;
	}
}