#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pos.h"
//Andrew DeVoe
// CMSC 152 - Project 1

//Makes a new pos with row r and column c
pos make_pos(unsigned int r, unsigned int c) {
    pos p;
    p.c = c;
    p.r = r;
    return p;
}

//Allocates and returns a new, empty queue
posqueue* posqueue_new() {
    posqueue *q = (posqueue*)malloc(sizeof(posqueue));
    if(q == NULL) {
        fprintf(stderr, "posqueue_new: error - could not allocate memory\n");
        exit(1);
    }
    q->head = NULL;
    q->tail = q->head;
    q->len = 0;
    return q;
}

//Prints a posqueue
void posqueue_print(posqueue *q) {
    pq_entry *temp = q->head;
    for(unsigned int i = 0; i < q->len; i++) {
        if(i == (q->len - 1)) {
            printf("(%d,%d)", temp->p.r, temp->p.c);
            temp = temp->next;
        } else {
            printf("(%d,%d) -> ", temp->p.r, temp->p.c);
            temp = temp->next;
        }
    }
}

//Enqueues the given pos at the end of the queue
void pos_enqueue(posqueue* q, pos p) {
    pq_entry *new = (pq_entry*)malloc(sizeof(pq_entry));
    if(new == NULL) {
        fprintf(stderr, "pos_enqueue: error - could not allocate memory\n");
        exit(1);
    }
    new->p = p;
    new->next = NULL;
    if(q->head == NULL) {
        q->head = new;
        q->tail = new;
    } else {
        q->tail->next = new;
        q->tail = q->tail->next;
    }
    q->len = q->len + 1;
}

//Dequeues and frees the head of the queue and returns its position
pos pos_dequeue(posqueue* q) {
    if(q->head == NULL) {
        fprintf(stderr, "pos_dequeue - error: empty queue\n");
        exit(1);
    }
    pq_entry *temp = q->head;
    q->head = q->head->next;
    q->len = q->len - 1;
    pos p = temp->p;
    free(temp);
    return p;
}

//Returns true if the pos is in the given queue, otherwise false
bool posqueue_member(posqueue* q, pos p) {
    pq_entry *temp = q->head;
    for(unsigned int i = 0; i < q->len; i++) {
        if((temp->p.c == p.c) && (temp->p.r = p.r)) {
            return true;
        } else {
            temp = temp->next;
        }
    }
    return false;
}

//Frees an entire queue
void posqueue_free(posqueue* q) {
    for(unsigned int i = 0; i < q->len; i++) {
        pq_entry *temp = q->head->next;
        free(q->head);
        q->head = temp;
    }
    free(q);
}
