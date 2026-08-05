#include <stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

//Member Methods :
Node* pushtoll(Node* head,int val);

typedef struct stack
{
    Node *head;
    int node_count;

}stack;
//Member Methods :
stack * stk_init();
int stk_size(stack * stk );
void stk_push(stack * stk, int val);
void stk_pop(stack * stk);
int stk_empty(stack * stk);
int stk_top(stack * stk);

typedef struct
{
    Node *head , *tail;
    int node_count;
    
}queue;
//Member Methods :
queue * queue_init();
int queue_size(queue * q );
void queue_push(queue * q, int val);
int queue_front(queue * q);
void queue_pop(queue * q);
int queue_empty(queue * q);

