#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int valor;
    struct node* next;
}node;

typedef struct stack{
    struct node* top;
}stack;

stack* init_stack(void){
    stack* s = (stack*)malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

// adds a element to the end of the stack
void push(stack* s, int valor){
    node* nnode = (node*)malloc(sizeof(node));
    nnode->valor = valor;
    nnode->next = NULL;
    s->top->next = nnode;
    s->top = nnode;
}

//pops the last element of the stack
void pop(stack* s){
    if (s->top == NULL)
        return;
    node* aux = s->top;
    s->top = s->top->next;
    free(aux);
}

// returns the top element of the stack
node* last(stack* s){
    return s->top;
}

