#include <stdio.h>
#include <stdlib.h>

// the start of a Depth First Search for a Tree 

typedef struct node{
    struct node* left;
    struct node* right;
    int value;
}node;

typedef struct tree{
    node* root;
}tree;

typedef struct queue{
    int front;
    int rear;
    node** data;
    int size;
    int cap;
    int factor;
}queue;

node* create_node(int value){
    node* nnode = (node*)malloc(sizeof(node));
    if (!nnode) return NULL;
    nnode->left = NULL;
    nnode->right = NULL;
    nnode->value = value;
    return nnode;
}

tree* create_tree(node* root){
    tree* t = (tree*)malloc(sizeof(tree));
    if (!t) return NULL;
    t->root = root;
    return t;
}

queue* create_queue(int initial_size){
    queue* q = (queue*)malloc(sizeof(queue));
    if (!q) return NULL;
    q->data = malloc(sizeof(node*) * initial_size);
    if (!q->data) return NULL;
    q->front = -1;
    q->rear = -2;
    q->size = 0;
    q->cap = initial_size;
    q->factor = 2; // for realloc
    return q;
}

void enqueue(queue* q, node* node){
    if (q->rear++ % q->cap == q->front) return;
    if (q->size == 0){ // queue vazia
       q->data[0] = node;
       q->front = 0;
       q->rear = 0;
    }
    else {
        q->data[q->rear++] = node;
        q->rear++ % q->cap;
    }
    q->size++;
}

void dequeue(queue* q){
    
}

void dfs(node* root){
    
}
