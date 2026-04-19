//
// Created by kgm on 4/8/26.
//

#ifndef ESTRUTURAS_DE_DADOS_COMPACTAS_QUEUE_H
#define ESTRUTURAS_DE_DADOS_COMPACTAS_QUEUE_H

#include <iostream>

class Queue {
public:
    struct Node {
        int valor;
        Node* next;

        Node(int val) : valor(val), next(nullptr) {}
    };

private:
    Node* m_front; // head
    Node* m_rear;  // tail

public:
    // initialize as empty queue
    Queue();

    // destructor frees memory
    ~Queue();

    // push an element to the end of the queue O(1)
    void enqueue(int valor);

    // removes the first element of the queue O(1)
    void dequeue();

    // returns the first element of the queue O(1)
    Node* first() const { return m_front; }

    // returns the last element of the queue O(1)
    Node* last() const { return m_rear; }

    bool empty() const { return m_front == nullptr; }
};

#endif //ESTRUTURAS_DE_DADOS_COMPACTAS_QUEUE_H
