//
// Created by kgm on 4/8/26.
//

#include "dll.h"

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
