#include <stdio.h>
#include <stdlib.h>

// A Single Linked List Implementation

typedef struct no{ // no creates a temporary buffer that makes so the next commented line gets interpreted by the compiler
    int data; // tipo de valor armazenado em no
    struct no* next; // this line makes so the next is created
} node; // alias of the struct = nickname = apelido

// insere um node de valor x no inicio da lista 
void inject(node** head, int x){
    node *nnode = (node*)malloc(sizeof(node));
    if (nnode){ 
        nnode->next = *head; // para aonde o head aponta atualemte
        *head = nnode;
        nnode->data = x;
    }
}

// deletes an element at the beggining of the list
void eject(node **head){
    if (head == NULL || *head == NULL) // if only head, do nothing
        return;
    node *element = *head;
    *head = (*head)->next;
    free(element);
}

// adds a element to the end of the list
void push(node **head, int x){
    node *nnode = (node*)malloc(sizeof(node));
    nnode->data = x;

    if (*head == NULL){ // if empty
        *head = nnode;
        nnode->next = NULL;
        return;
    }

    node *curr = *head;
    while(curr->next){
        curr = curr->next;
    }
    curr->next = nnode;
    nnode->next = NULL;
}

// deletes the last element from the list
void pop(node **head){
    if (*head == NULL) return;           // empty
    if ((*head)->next == NULL) {         // only one node
        free(*head);
        *head = NULL;
        return;
    }
    node *prev = *head;
    node *curr = (*head)->next;
    while(curr->next){
        prev = prev->next;
        curr = curr->next;
    }
    prev->next = NULL;
    free(curr);
}

// search a element with a given key = value = x. Kind of a ISIN function
void get(node *head, int x){
    node *curr = head;
    while(curr){
        if (curr->data == x){
            printf("%d is in the list\n", x);
            return;
        }
        curr = curr->next;
    }
}   

// changes the value of x to y
void set(node *head, int x, int y){
    node *curr = head;
    while(curr){
        if (curr->data == x){
            curr->data = y;
            return;
        }
        curr = curr->next;
    }
}

// deletes a element with data = x
void delete_specific(node **head, int x){
    if (*head == NULL) return; //empty
    if ((*head)->next == NULL){ // one element 
        free(*head);
        *head = NULL;
        return;
    }
    
    node *prev = *head;
    node *curr = (*head)->next;

    //check first elemen
    if (curr->data == x){
        prev->next = curr->next;
        free(curr);
        return;


    while(curr){
        if (curr->data == x){
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = prev->next;
        curr = curr->next;
    }
}

// printa os elementos da lista
void print(node *head){
    printf("LISTA: ");
    node *curr = head;
    while(curr){
        printf("%d->", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

// ISEMPTY
void empty(node *head){
    if (head == NULL){
        printf("empty\n");
        return;
    }
    printf("not empty\n");
}

int main (void){
    node *head = NULL;
    empty(head); // empty
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    print(head); //LISTA: 1->2->3->4->NULL
    empty(head); // not empty
    pop(&head);
    print(head);  //LISTA: 1->2->3->NULL
    eject(&head);
    inject(&head, 100);
    print(head);  //LISTA: 100->2->3->NULL
    get(head, 4); 
    get(head, 100); // 100 esta na lista
    set(&head, 100, 0);
    print(head); //  //LISTA: 0->2->3->NULL
    eject(&head);
    pop(&head);
    print(head);  //LISTA: 2->NULL
    pop(&head);
    empty(head); // empty
    print(head);  //LISTA: NULL
}
