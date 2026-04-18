//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_QUEUE_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_QUEUE_H
#include <stdio.h>
#include <stdlib.h>

// A linked list queue implementation

typedef struct node{
    int valor;
    struct node* next;
}node;

typedef struct queue{
    node* front; // head
    node* rear; // tail
}queue;

// creates a empty queue
queue* create_queue(void);
// push a element to the end of the queue O(1)
void enqueue(queue* q, node* element);

// ejects and returns the first element of the queue O(1)
void dequeue(queue* q);

// returns the first element of the queue O(1)
node* first(queue* q);

// returns the last element of the queue O(1)
node* last(queue* q);

#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_QUEUE_H
