#include <stdio.h>
#include "pos.h"
#include "board.h"
#include "logic.h"
//Andrew DeVoe
//CMSC 152 - Project 1

//TEST pos.c functions ————————————————————————————————————————————————————————

//Tests the make_pos function
void test_make_pos() {
    printf("*** Testing make_pos ***\n");
    unsigned int r = 0;
    unsigned int c = 0;
    //Test 1
    pos test = make_pos(r, c);
    printf("--- expecting r=0, c=0: r=%d, c=%d\n", test.r, test.c);
    //Test 2
    r = 6;
    c = 28;
    test = make_pos(r, c);
    printf("--- expecting r=6, c=28: r=%d, c=%d\n", test.r, test.c);
    printf("\n");
}

//Tests the posqueue_new and posqueue_free functions
void test_new_free_posqueue() {
    printf("*** Testing posqueue_new and posqueue_free ***\n");
    posqueue *q = posqueue_new();
    printf("--- expecting 0: %d\n", q->len);
    posqueue_free(q);
    printf("\n");
}

//Tests the pos_enqueue, pos_dequeue, and posqueue_print functions
void test_enqueue_dequeue_print_posqueue() {
    printf("*** Testing pos_enqueue, pos_dequeue, and posqueue_print ***\n");
    posqueue *q = posqueue_new();
    /* printf("--- expecting error: \n");
     * pos_dequeue(q);
     */
    pos_enqueue(q, make_pos(3,4));
    pos_enqueue(q, make_pos(0,1));
    pos_enqueue(q, make_pos(5,2));
    pos_enqueue(q, make_pos(6,8));
    printf("--- expecting 4: %d\n", q->len);
    printf("--- expecting (3,4) -> (0,1) -> (5,2) -> (6,8): ");
    posqueue_print(q);
    printf("\n");
    pos temp = pos_dequeue(q);
    printf("--- expecting (3,4): (%d,%d)\n", temp.r, temp.c);
    printf("--- expecting 3: %d\n", q->len);
    printf("--- expecting (0,1) -> (5,2) -> (6,8): ");
    posqueue_print(q);
    printf("\n");
    temp = pos_dequeue(q);
    printf("--- expecting (0,1): (%d,%d)\n", temp.r, temp.c);
    printf("--- expecting 2: %d\n", q->len);
    printf("--- expecting (5,2) -> (6,8): ");
    posqueue_print(q);
    printf("\n");
    posqueue_free(q);
    printf("\n");
}

//Tests the posqueue_member function
void test_posqueue_member() {
    printf("*** Testing posqueue_member ***\n");
    posqueue *q = posqueue_new();
    pos p1 = make_pos(3,4);
    pos p2 = make_pos(5,2);
    pos p3 = make_pos(6,8);
    pos_enqueue(q, p1);
    pos_enqueue(q, make_pos(0,1));
    pos_enqueue(q, p2);
    pos_enqueue(q, p3);
    printf("--- expecting 1: %d\n", posqueue_member(q, p1));
    printf("--- expecting 1: %d\n", posqueue_member(q, p2));
    printf("--- expecting 1: %d\n", posqueue_member(q, p3));
    printf("--- expecting 0: %d\n", posqueue_member(q, make_pos(0,0)));
    printf("--- expecting 0: %d\n", posqueue_member(q, make_pos(2,5)));
    printf("--- expecting 0: %d\n", posqueue_member(q, make_pos(1,7)));
    posqueue_free(q);
    printf("\n");
}

//TEST board.c functions ——————————————————————————————————————————————————————

//Tests the board_new, board_show (and get_letter), and board_free functions
void test_board_new_show_free() {
    printf("*** Testing board_new, board_show, and board_free ***\n");
    unsigned int w = 8;
    unsigned int h = 4;
    enum type mat = MATRIX; 
    printf("--- expecting (visually inspect) a new, empty 8x4 board: \n");
    board *b = board_new(w, h, mat);
    board_show(b);
    board_free(b);
    printf("\n");
    w = 65;
    h = 65;
    printf("--- expecting (visually inspect) a new, empty 65x65 board: \n");
    b = board_new(w, h, mat);
    board_show(b);
    board_free(b);
    printf("\n");
    w = 27;
    h = 18;
    printf("--- expecting (visually inspect) a new, empty 27x18 board: \n");
    b = board_new(w, h, mat);
    board_show(b);
    board_free(b);
    printf("\n");
}

//Testing the board_get and board_set functions
void test_board_get_set() {
    printf("*** Testing board_get and board_set ***\n");
    unsigned int w = 8;
    unsigned int h = 4;
    enum type mat = MATRIX; 
    board *b = board_new(w, h, mat);
    pos p1 = make_pos(2,2);
    pos p2 = make_pos(3,4);
    //pos out = make_pos(8,9);
    //Test 1
    board_show(b);
    printf("\n");
    printf("--- expecting 0: %d\n", board_get(b, p1));
    //Test 2
    board_set(b, p2, BLACK);
    board_show(b);
    printf("\n");
    printf("--- expecting 1: %d\n", board_get(b, p2));
    //Test 3
    board_set(b, p1, WHITE);
    board_show(b);
    printf("\n");
    //Test 4
    printf("--- expecting 2: %d\n", board_get(b, p1));
    board_show(b);
    printf("\n");
    //Test 5
    /* printf("--- expecting error: \n");
     * board_set(b, out, WHITE);
     * board_get(b, out);
     */
    board_free(b);
}

//TEST logic.c functions ——————————————————————————————————————————————————————

//Tests the new_game and game_free functions
void test_new_game_free() {
    printf("*** Testing new_game and game_free ***\n");
    unsigned int run = 3;
    unsigned int hang = 2;
    unsigned int w = 8;
    unsigned int h = 4;
    enum type mat = MATRIX;
    game *g = new_game(run, hang, w, h, mat);
    printf("--- expecting run 3: %d\n", g->run);
    printf("--- expecting hang 2: %d\n", g->hangtime);
    printf("--- expecting players_turn 0: %d\n", g->player);
    printf("--- expecting 4x8 board:\n");
    board_show(g->b);
    printf("\n");
    game_free(g);
}

//Tests the place_piece (+fall) and game_outcome (+get_run) functions
void test_place_piece_outcome() {
    printf("*** Testing place_piece and game_outcome ***\n");
    unsigned int run = 3;
    unsigned int hang = 2;
    unsigned int w = 8;
    unsigned int h = 4;
    enum type mat = MATRIX;
    game *g = new_game(run, hang, w, h, mat);
    //Move 1
    printf("Move 1\n");
    printf("--- expecting 1: %d\n", place_piece(g, make_pos(1,1)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 2 (fail)
    printf("Move 2 (fail)\n");
    printf("--- expecting 0: %d\n", place_piece(g, make_pos(10,1)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 2 (succeed)
    printf("Move 2 (succeed)\n");
    printf("--- expecting 1: %d\n", place_piece(g, make_pos(0,3)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 3
    printf("Move 3\n");
    printf("--- expecting 1: %d\n", place_piece(g, make_pos(2,3)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 4 (fail)
    printf("Move 4 (fail)\n");
    printf("--- expecting 0: %d\n", place_piece(g, make_pos(3,1)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 4 (succeed)
    printf("Move 4 (succeed)\n");
    printf("--- expecting 1: %d\n", place_piece(g, make_pos(1,2)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 5
    printf("Move 5\n");
    printf("--- expecting 1: %d\n", place_piece(g, make_pos(0,2)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    printf("\n");
    //Move 6
    printf("Move 6\n");
    printf("--- expecting 1: %d\n", place_piece(g, make_pos(1,4)));
    board_show(g->b);
    printf("hanging queue: ");
    posqueue_print(g->hanging);
    printf("\n");
    printf("--- expecting outcome 2: %d\n", game_outcome(g));
    game_free(g);
    printf("\n");
}

//Tests more outcomes (mainly wins and draws)
void test_more_outcomes() {
    printf("*** Testing more outcomes for game_outcome ***\n");
    unsigned int run = 3;
    unsigned int hang = 2;
    unsigned int w = 8;
    unsigned int h = 4;
    enum type mat = MATRIX;
    game *g = new_game(run, hang, w, h, mat);
    //Test 1 Horrizontal
    board_set(g->b, make_pos(0,1), BLACK);
    board_set(g->b, make_pos(0,2), BLACK);
    board_set(g->b, make_pos(0,3), BLACK);
    printf("--- expecting outcome 1: %d\n", game_outcome(g));
    //Test 2 Vertical
    board_set(g->b, make_pos(0,2), EMPTY);
    board_set(g->b, make_pos(0,3), EMPTY);
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    board_set(g->b, make_pos(1,1), BLACK);
    board_set(g->b, make_pos(2,1), BLACK);
    printf("--- expecting outcome 1: %d\n", game_outcome(g));
    //Test 3 Positive slope
    board_set(g->b, make_pos(0,1), EMPTY);
    board_set(g->b, make_pos(1,1), EMPTY);
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    board_set(g->b, make_pos(1,2), BLACK);
    board_set(g->b, make_pos(0,3), BLACK);
    printf("--- expecting outcome 1: %d\n", game_outcome(g));
    //Test 4 Negative slope
    board_set(g->b, make_pos(2,1), EMPTY);
    board_set(g->b, make_pos(1,2), EMPTY);
    board_set(g->b, make_pos(0,3), EMPTY);
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    board_set(g->b, make_pos(0,1), WHITE);
    board_set(g->b, make_pos(1,2), WHITE);
    board_set(g->b, make_pos(2,3), WHITE);
    printf("--- expecting outcome 2: %d\n", game_outcome(g));
    //Test 5 Draw white negative slope, black horrizontal
    board_set(g->b, make_pos(3,2), BLACK);
    board_set(g->b, make_pos(3,3), BLACK);
    board_set(g->b, make_pos(3,4), BLACK);
    printf("--- expecting outcome 3: %d\n", game_outcome(g));
    //Test 6 Full board
    board_set(g->b, make_pos(3,2), EMPTY);
    board_set(g->b, make_pos(3,3), EMPTY);
    board_set(g->b, make_pos(3,4), EMPTY);
    board_set(g->b, make_pos(0,1), EMPTY);
    board_set(g->b, make_pos(1,2), EMPTY);
    board_set(g->b, make_pos(2,3), EMPTY);
    printf("--- expecting outcome 0: %d\n", game_outcome(g));
    board_set(g->b, make_pos(0,0), WHITE);
    board_set(g->b, make_pos(1,0), WHITE);
    board_set(g->b, make_pos(2,0), BLACK);
    board_set(g->b, make_pos(3,0), BLACK);
    board_set(g->b, make_pos(0,1), BLACK);
    board_set(g->b, make_pos(1,1), BLACK);
    board_set(g->b, make_pos(2,1), WHITE);
    board_set(g->b, make_pos(3,1), WHITE);
    board_set(g->b, make_pos(0,2), WHITE);
    board_set(g->b, make_pos(1,2), WHITE);
    board_set(g->b, make_pos(2,2), BLACK);
    board_set(g->b, make_pos(3,2), BLACK);
    board_set(g->b, make_pos(0,3), BLACK);
    board_set(g->b, make_pos(1,3), BLACK);
    board_set(g->b, make_pos(2,3), WHITE);
    board_set(g->b, make_pos(3,3), WHITE);
    board_set(g->b, make_pos(0,4), WHITE);
    board_set(g->b, make_pos(1,4), WHITE);
    board_set(g->b, make_pos(2,4), BLACK);
    board_set(g->b, make_pos(3,4), BLACK);
    board_set(g->b, make_pos(0,5), BLACK);
    board_set(g->b, make_pos(1,5), BLACK);
    board_set(g->b, make_pos(2,5), WHITE);
    board_set(g->b, make_pos(3,5), WHITE);
    board_set(g->b, make_pos(0,6), WHITE);
    board_set(g->b, make_pos(1,6), WHITE);
    board_set(g->b, make_pos(2,6), BLACK);
    board_set(g->b, make_pos(3,6), BLACK);
    board_set(g->b, make_pos(0,7), BLACK);
    board_set(g->b, make_pos(1,7), BLACK);
    board_set(g->b, make_pos(2,7), WHITE);
    board_set(g->b, make_pos(3,7), WHITE);
    printf("--- expecting outcome 3: %d\n", game_outcome(g));
    game_free(g);
}

//Main ————————————————————————————————————————————————————————————————————————

int main(int argc, char *argv[]) {
    //Pos testing functions
    test_make_pos();
    test_new_free_posqueue();
    test_enqueue_dequeue_print_posqueue();
    test_posqueue_member();

    //Board testing functions
    test_board_new_show_free();
    test_board_get_set();

    //Logic testing functions
    test_new_game_free();
    test_place_piece_outcome();
    test_more_outcomes();

    return 0;
}