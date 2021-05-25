#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "board.h"
//Andrew DeVoe
// CMSC 152 - Project 1

//Makes a new, empty board
board* board_new(unsigned int width, unsigned int height, enum type type) {
    if(type == BITS) {
        fprintf(stderr, "board_new: error - BITS requested\n");
        exit(1);
    } else if(type >= 2) {
        fprintf(stderr, "board_new: error - type too large\n");
        exit(1);
    } else if((width == 0) || (height == 0)) {
        fprintf(stderr, "board_new: error - board must be at least 1x1\n");
        exit(1);
    }
    board *b = (board*)malloc(sizeof(board));
    if(b == NULL) {
        fprintf(stderr, "board_new: error - could not allocate memory\n");
        exit(1);
    }
    b->height = height;
    b->width = width;
    b->type = type;
    cell **matrix = (cell**)malloc(height * sizeof(cell*));
    if(matrix == NULL) {
        fprintf(stderr, "board_new: error - could not allocate memory\n");
        exit(1);
    }
    for(unsigned int i = 0; i < height; i++) {
        matrix[i] = (cell*)malloc(width * sizeof(cell));
        if(matrix[i] == NULL) {
            fprintf(stderr, "board_new: error - could not allocate memory\n");
            exit(1);
        }
        for(unsigned int j = 0; j < width; j++) {
            matrix[i][j] = EMPTY;
        }
    }
    b->u.matrix = matrix;
    return b;
}

//Frees an entire board
void board_free(board* b) {
    for(unsigned int i = 0; i < b->height; i++) {
        free(b->u.matrix[i]);
    }
    free(b->u.matrix);
    free(b);
}

//Gets the proper letter if the board is longer than 10
char get_letter(unsigned int spot) {
    if((spot >= 10) && (spot <= 35)) {
        return (char) spot + 55;
    } else if((spot >= 36) && (spot <= 61)) {
        return (char) spot + 61;
    } else {
        return '?';
    }
}

//Prints the board
void board_show(board* b) {
    for(unsigned int i = 0; i < b->height + 2; i++) {
        if(i == 1) {
            printf("\n");
            continue;
        }
        for(unsigned int j = 0; j < b->width + 2; j++) {
            if(i == 0) {
                if(j < 2) {
                    printf(" ");
                } else if(j - 2 < 10) {
                    printf("%d", j - 2);
                } else {
                    printf("%c", get_letter(j - 2));
                }
            } else if(j == 0) {
                if(i - 2 < 10) {
                    printf("%d", i - 2);
                } else {
                    printf("%c", get_letter(i - 2));
                }
            } else if(j == 1){
                printf(" ");
            } else {
                if(b->u.matrix[i-2][j-2] == BLACK) {
                    printf("*");
                } else if(b->u.matrix[i-2][j-2] == WHITE) {
                    printf("o");
                } else {
                    printf(".");
                }
            }
        }
        printf("\n");
    }
}

//Gets the cell in the board at pos p
cell board_get(board* b, pos p) {
    if(b->type != MATRIX) {
        fprintf(stderr, "board_get: error - board not matrix\n");
        exit(1);
    } else if((p.r > b->height) || (p.c > b->width)) {
        fprintf(stderr, "board_get: error - pos not in board\n");
        exit(1);
    }
    return b->u.matrix[p.r][p.c];
}

//Sets the cell in the board at pos p as cell c
void board_set(board* b, pos p, cell c){
    if(b->type != MATRIX) {
        fprintf(stderr, "board_set: error - board not matrix\n");
        exit(1);
    } else if((p.r >= b->height) || (p.c >= b->width)) {
        fprintf(stderr, "board_set: error - pos not in board\n");
        exit(1);
    }
    b->u.matrix[p.r][p.c] = c;
}