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
queue* create_queue(void){
    queue* q = (queue*)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    return q;
}

// push a element to the end of the queue O(1)  
void enqueue(queue* q, node* element){
    if (q->front == NULL) // empty queue
        q->front = q->rear = element;
    else{
        q->rear->next = element;
        element->next = NULL; // added at the end of the queue
        q->rear = element;
    }
}

// ejects and returns the first element of the queue O(1)
void dequeue(queue* q){
    if (q->front == NULL)
        return;
    else if (q->front->next == NULL) {// only one element
        node* aux = q->front;
        q->front = NULL;
        q->rear = NULL;
        free(aux);
    }
    else{
        node* temporary = q->front;
        q->front = q->front->next;
        free(temporary);
    }
}

// returns the first element of the queue O(1)
node* first(queue* q){
    return (q->front);
}

// returns the last element of the queue O(1)
node* last(queue* q){
    return (q->rear);
}
