//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_LL2_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_LL2_H

#include <stdio.h>
#include <stdlib.h>

// A List ADT Implementation using Linked Lists

typedef struct node{
    long valor;
    struct node* next;
} node;

typedef struct list{
    node* head;
    node* tail;
    long size;
}list;

// initialize as empty new list L
list* alloc_list(void);

// libera a memoria ocupada pela lista e da lista em si
void free_list(list *L);

// printa a lista como esta
void print_list(list *L);

// cria e insere um node nnode no inicio da linked list
void insert(list* L, long valor);

// deletes the element at the beggining of the list
void eject(list* L);

// adds a element at the end of the list
void push(list* L, long valor);
// exclui o ultimo elemento da lista
void pop(list* L);

// devolve o valor do elemento na posicao index
void get(list* L, size_t index);

// troca o valor de um elemento com valor_antigo para valor_novo
void set(list* L, long valor_antigo, long valor_novo);
#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_LL2_H
