#include <stdio.h>
#include <stdlib.h>

// A Double Linked List Implementation

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
list* alloc_list(void){
    list* L = malloc(sizeof(list));
    if (L){
        L->head = NULL;
        L->tail = NULL;
        L->size = 0;
    }
    return L;
}

// libera a memoria ocupada pela lista e da lista em si
void free_list(list *L){
    //caso lista vazia
    if (L->head == NULL && L->tail == NULL){
        free(L);
        return;
    }
    //caso 1 elemento
    if (L->head->next == NULL){
        free(L->head);
        free(L);
        return;
    }
    //caso geral
    node* curr = L->head;
    node* aux = NULL;
    while(curr){
        aux = curr->next;
        free(curr);
        curr = aux;
    }
    free(L);
}

// printa a lista como esta
void print_list(list *L){
    node* temporary = L->head; // para aonde head aponta
    printf("List(%ld): ", L->size);
    while(temporary){
        printf("%ld->", temporary->valor);
        temporary = temporary->next;
    }
    printf("NULL\n");
}

// cria e insere um node nnode no inicio da linked list
void insert(list* L, long valor){
    node* nnode = malloc(sizeof(node));
    if (nnode){
        nnode->valor = valor;
        // considerar lista vazia
        if (L->head == NULL && L->tail == NULL){
            L->head = nnode;
            L->tail = nnode;
            nnode->next = NULL;
        }
        else {
            nnode->next = L->head; // para aonde o head da lita aponta
            L->head = nnode;
        }
        L->size++;
    }
}

// deletes the element at the beggining of the list
void eject(list* L){
    if(L->head != NULL && L->tail != NULL){
        node* temporary = L->head; 
        if (L->head->next == NULL){ // 1 elemento 
            free(temporary);
            L->tail = NULL;
            L->head = NULL;
            L->size--;
            return;
        }
        L->head = L->head->next;
        free(temporary);
        L->size--;
    }
}

// adds a element at the end of the list
void push(list* L, long valor){
    node* nnode = malloc(sizeof(node));
    nnode->valor = valor;
    // considerar lista vazia
    if (L->head == NULL && L->tail == NULL){
        L->head = nnode;
        L->tail = nnode;
        nnode->next = NULL;
    } 
    else{
        L->tail->next = nnode;
        L->tail = nnode;
        nnode->next = NULL;
    }
    L->size++;
}

// exclui o ultimo elemento da lista
void pop(list* L){
    if (L->head != NULL && L->tail != NULL){
        node* temporary = L->tail;
        if (L->head->next == NULL){ // 1 elemento
            free(temporary);
            L->head = NULL;
            L->tail = NULL;
        }
        else{
            node* curr = L->head;
            while(curr->next != temporary)
                curr = curr->next;
            L->tail = curr;
            curr->next = NULL;
            free(temporary);
        }
        L->size--;
    }
}

// devolve o valor do elemento na posicao index 
void get(list* L, size_t index){
    node* temporary = L->head;
    for (int i = 0; i < L->size; i++){
        if (i == index){
            printf("get(%zu): %ld\n",index,temporary->valor);
            return;
        }
        temporary = temporary->next;
    }
    printf("index out of range\n");
}

// troca o valor de um elemento com valor_antigo para valor_novo
void set(list* L, long valor_antigo, long valor_novo){
    node* temporary = L->head;
    while(temporary){
        if (temporary->valor == valor_antigo){
            temporary->valor = valor_novo;
            return;
        }
        temporary = temporary->next;
    }
}

int main(void){
    // criar lista vazia
    list *L = malloc(sizeof(list));
    L->head = NULL;
    L->tail = NULL;
    L->size = 0;

    // insert(L, 0);
    // insert(L, 1);
    // insert(L, 2);
    // insert(L, 3);
    // insert(L, 4);
    // print_list(L);
    // eject(L);
    // print_list(L);
    // push(L, 100);
    // print_list(L);
    // set(L, 100, -1);
    // print_list(L);
    // pop(L);
    // print_list(L);
    // get(L, 0);
    // get(L, 1);
    // get(L, 2);
    // get(L, 3);
    // get(L, 4);
    // eject(L);
    // pop(L);
    // print_list(L);
    // eject(L);
    // pop(L);
    // print_list(L);
    // pop(L);

    push(L, 12);
    print_list(L);
    eject(L);
    print_list(L);
    free_list(L);
}
