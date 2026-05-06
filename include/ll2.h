//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_LL2_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_LL2_H

#include <iostream>
#include <cstddef>

class LinkedList {
public:
    struct Node {
        long valor;
        Node* next;

        Node(long val) : valor(val), next(nullptr) {}
    };

private:
    Node* m_head;
    Node* m_tail;
    long m_size;

public:
    // initialize as empty new list
    LinkedList();

    // destructor frees the memory used by the list
    ~LinkedList();

    // print the list as it is
    void print() const;

    // create and insert a node at the beginning of the linked list
    void insert(long valor);

    // delete the element at the beginning of the list
    void eject();

    // add an element at the end of the list
    void push(long valor);

    // remove the last element of the list
    void pop();

    // get the value of the element at position index
    void get(size_t index) const;

    // change the value of an element from old_value to new_value
    void set(long old_value, long new_value);

    long size() const { return m_size; }
};

#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_LL2_H
