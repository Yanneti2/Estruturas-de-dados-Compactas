//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_STACK_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_STACK_H
#include <stdio.h>
#include <stdlib.h>

// A linked list implementation of a stack

typedef struct node{
    int valor;
    struct node* next;
}node;

typedef struct stack{
    struct node* top;
}stack;

stack* init_stack(void);
// adds a element to the end of the stack
void push(stack* s, int valor);

//pops the last element of the stack
void pop(stack* s);

// returns the top element of the stack
node* last(stack* s);


#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_STACK_H
