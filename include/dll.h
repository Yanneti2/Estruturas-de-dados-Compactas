//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_DLL_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_DLL_H

#include <stdio.h>
#include <stdlib.h>

// Double Linked List Implementation

typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
}node;

typedef struct list{
    long size;
    node* head;
    node* tail;
}list;

// creates a empty list O(1)
list* init_list(void);

// frees the memory used to store the list before exiting the program
void free_list(list* L);


// printa a lista em uma linha O(n)
void print_list(list* L);


// insere um node com data = valor no inicio da lista O(1)
void insert(list* L, int valor);

// remove o primeiro elemento de uma lista O(1)
void eject(list* L);

// adds a node to the end of the list O(1)
void push(list* L, int valor);

// deletes a element at the end of the list O(1)
void pop(list* L);

// gets the element at index and prints it O(n)

// pode ser O(1) se  guardar o index de cada elemento na lista

// If you want to get the element at index, and index is in the
// first half of the list, search forward from the head. If it's
// in the second half, search backward from the tail. This can cut
// your maximum search time in half O(n/2)
void get(list* L, size_t index);

// sets a element of data x to data = y
void set(list* L, int x, int y);

// inserts a element at a given position O(n)
void insert_at(list* L, int valor, size_t index);

// removes a element at a given position
void remove_at(list* L, size_t index);

// reverses the order of the dll
void reverse(list* L);

#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_DLL_H
