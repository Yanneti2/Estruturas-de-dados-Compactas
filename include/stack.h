//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_STACK_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_STACK_H

#include <iostream>

class Stack {
public:
    struct Node {
        int valor;
        Node* next;

        Node(int val) : valor(val), next(nullptr) {}
    };

private:
    Node* m_top;

public:
    // initialize as empty stack
    Stack();

    // destructor frees the memory used by the stack
    ~Stack();

    // adds an element to the top of the stack
    void push(int valor);

    // pops the top element of the stack
    void pop();

    // returns the top element of the stack
    Node* last() const;

    bool empty() const { return m_top == nullptr; }
};

#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_STACK_H
