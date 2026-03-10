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
list* init_list(void){
    list* L = malloc(sizeof(list));
    if (L){
        L->size = 0;
        L->head = NULL;
        L->tail = NULL;
    }
    return L;
}

// frees the memory used to store the list before exiting the program
void free_list(list* L){
    if (L){
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
        node* curr = L->head;
        while (curr){
            node* aux = curr;
            curr = curr->next;
            free(aux);
        }
        free(L);
    }
}

// printa a lista em uma linha O(n)
void print_list(list* L){
    printf("LISTA(%ld): NULL <->", L->size);
    node* curr = L->head;
    while (curr){
        printf(" %d <->", curr->data);
        curr = curr->next;
    }
    printf(" NULL\n");
}

// insere um node com data = valor no inicio da lista O(1)
void insert(list* L, int valor){
    node* nnode = malloc(sizeof(node));
    if (nnode){
        nnode->data = valor;
        if (L->head == NULL && L->tail == NULL){ // lista vazia
            L->head = nnode;
            L->tail = nnode;
            nnode->next = NULL;
            nnode->prev = NULL;
        }
        else {
            nnode->next = L->head; 
            nnode->prev = NULL;
            L->head->prev = nnode;
            L->head = nnode;
        }
        L->size++;
    }
}

// remove o primeiro elemento de uma lista O(1)
void eject(list* L){
    if (L){
        if (L->head == NULL && L->tail == NULL) return; // lista vazia
        
        node* aux = L->head;
        if (L->head->next == NULL){ //lista unitaria
            L->tail = NULL;
            L->head = NULL;
        }
        else{ // caso geral
            aux->next->prev = NULL;
            L->head = aux->next;
        }
        free(aux);
        L->size--;
    }
}

// adds a node to the end of the list O(1)
void push(list* L, int valor){
    node* nnode = malloc(sizeof(node));
    if (nnode){
        nnode->data = valor;
        if (L->head == NULL && L->tail == NULL){
            L->head = nnode;
            L->tail = nnode;
            nnode->next = NULL;
            nnode->prev = NULL;
        }
        else{
            L->tail->next = nnode;
            nnode->prev = L->tail;
            L->tail = nnode;
            nnode->next = NULL;
        }
        L->size++;
    }
}

// deletes a element at the end of the list O(1)
void pop(list* L){
    if (L){
        if (L->head == NULL && L->tail == NULL) return;
        node* aux = L->tail;
        if (L->head->next == NULL){
            L->head = NULL;
            L->tail = NULL;
        }
        else{
            aux->prev->next = NULL;
            L->tail = aux->prev;
        }
        free(aux);
        L->size--;
    }
}

// gets the element at index and prints it O(n)

// pode ser O(1) se  guardar o index de cada elemento na lista

// If you want to get the element at index, and index is in the 
// first half of the list, search forward from the head. If it's 
// in the second half, search backward from the tail. This can cut 
// your maximum search time in half O(n/2)
void get(list* L, size_t index){
    if (index < 0 || index > L->size){
        printf("index out of range\n");
        return;
    }
    node* aux = L->head;
    for (int i = 0; i < L->size; i++){
        if (i == index){
            printf("get(%zu): %d\n", index, aux->data);
            return;
        }
        aux = aux->next;
    }
}

// sets a element of data x to data = y
void set(list* L, int x, int y){
    node* aux = L->head;
    while (aux){
        if (aux->data == x){
            aux->data = y;
            return;
        }
        aux = aux->next;
    }
}

// inserts a element at a given position O(n)
void insert_at(list* L, int valor, size_t index){
    if (index < 0 || index > L->size){
        printf("index out of range\n");
        return;
    }
    else if (index == 0){ // casos de borda
        insert(L, valor);
        return;
    }
    else if (index == L->size){
        push(L, valor);
        return;
    }

    node* nnode = malloc(sizeof(node));
    if (nnode){
        nnode->data = valor;  
        node* curr = L->head;
        for (int i = 0; i < L->size; i++){
            if (i == index)
                break;
            curr = curr->next;
        }
        node* anterior = curr->prev;

        nnode->next = curr;
        anterior->next = nnode;
        nnode->prev = anterior;
        curr->prev = nnode;
        L->size++;
    }
}

// removes a element at a given position
void remove_at(list* L, size_t index){
    if (index < 0 || index > L->size){
        printf("index out of range\n");
        return;
    }
    else if (index == 0){ // casos de borda
        eject(L);
        return;
    }
    else if (index == L->size -1){
        pop(L);
        return;
    }

    if (L){
        node* aux = L->head;
        for (int i= 0; i < L->size; i++){
            if (i == index)
                break;
            aux = aux->next;
        }
        node* anterior = aux->prev;
        node* posterior = aux->next;
        anterior->next = posterior;
        posterior->prev = anterior;
        free(aux);
        L->size--;
    }
}

// reverses the order of the dll
void reverse(list* L){
    node* curr = L->head;
    node* temporary = NULL;
    while (curr){
        temporary = curr->prev;
        curr->prev = curr->next;
        curr->next = temporary;
        curr = curr->prev; // go to next in reverse order
    }
    temporary = L->head;
    L->head = L->tail;
    L->tail = temporary;
}

int main(void){
    list* lista = init_list();
    insert(lista, 0);
    insert(lista, 1);
    insert(lista, 2);
    insert(lista, 3);
    print_list(lista);
    eject(lista);
    print_list(lista);
    eject(lista);
    eject(lista);
    push(lista, 2);
    push(lista, 4);
    push(lista, 8);
    print_list(lista);
    pop(lista);
    print_list(lista);
    get(lista, 0);
    get(lista, 1);
    get(lista, 2);
    get(lista, 3);
    get(lista, -1);
    get(lista, 4);
    set(lista, 4, 2);
    set(lista, 0, 2);
    set(lista, -1, 100);
    print_list(lista);
    insert_at(lista, 20, 1);
    print_list(lista);
    insert_at(lista, 10, 0);
    print_list(lista);
    remove_at(lista, 2);
    print_list(lista);
    reverse(lista);
    print_list(lista);
    free_list(lista);
    return 0;
}
