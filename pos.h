#ifndef POS_H
#define POS_H

#include <stdbool.h>
//Andrew DeVoe
// CMSC 152 - Project 1

struct pos {
    unsigned int r, c;
};

typedef struct pos pos;


typedef struct pq_entry pq_entry;

struct pq_entry {
    pos p;
    pq_entry* next;
};


struct posqueue {
    pq_entry *head, *tail;
    unsigned int len;
};

typedef struct posqueue posqueue;

//Makes a new pos with row r and column c
pos make_pos(unsigned int r, unsigned int c);

//Allocates and returns a new, empty queue
posqueue* posqueue_new();

//Prints a posqueue
void posqueue_print(posqueue *q);

//Enqueues the given pos at the end of the queue
void pos_enqueue(posqueue* q, pos p);

//Dequeues and frees the head of the queue and returns its position
pos pos_dequeue(posqueue* q);

//Returns true if the pos is in the given queue, otherwise false
bool posqueue_member(posqueue* q, pos p);

//Frees an entire queue
void posqueue_free(posqueue* q);

#endif /* POS_H */
