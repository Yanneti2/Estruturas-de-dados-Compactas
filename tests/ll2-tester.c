//
// Created by kgm on 4/8/26.
//


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