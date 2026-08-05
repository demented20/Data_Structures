#include <stdio.h>
#include<stdlib.h>

// int linked list definition 

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* pushtoll(Node* head,int val){
    if (head == NULL) {
        Node * newhead = malloc(sizeof(Node));
        if(!newhead) return NULL;
        newhead->data = val;
        head = newhead;
        return head ;
    }
    else {
        Node * newhead = malloc(sizeof(Node));
        newhead->data = val;
        newhead->next = head;
        head = newhead;
        return newhead;
    }
} 
// int stack implementation and member function defintion 
typedef struct stack
{
    Node *head;
    int node_count;

}stack;
// operations : inti()/top()/push()/pop()/size()/empty()
stack * stk_init(){
    stack * newStack = malloc(sizeof(stack));
    if(!newStack) return NULL;
    newStack->head = NULL;
    newStack->node_count = 0;
    return newStack;
}
int stk_size(stack * stk ){
    return stk->node_count;
}

void stk_push(stack * stk, int val){
    Node * new_data = malloc(sizeof(Node)) ;
    new_data->data = val;
    new_data->next = stk->head;
    stk->head = new_data;
    stk->node_count++;
}
void stk_pop(stack * stk){
    if(stk->node_count == 0) return ;
    else {
        Node * trash = stk->head;
        stk->head = stk->head->next;
        free(trash);
        stk->node_count--;
    }
}
int stk_empty(stack * stk){
    if(stk->node_count == 0) return 1;
    else return 0;
}
int stk_top(stack * stk){
    if(stk->node_count == 0) return -1;
    else return stk->head->data;
}

// int queue implementation and member function defintion 
typedef struct queue
{
    Node *head , *tail;
    int node_count;
    
}queue;

queue * queue_init(){
    queue * newQueue = malloc(sizeof(queue));
    if (!newQueue) return NULL;
    newQueue->head = NULL;
    newQueue->tail = NULL;
    newQueue->node_count = 0;
    return newQueue;
}
int queue_size(queue * q ){
    return q->node_count;
}
void queue_push(queue * q, int val){
    Node * new_node = malloc(sizeof(Node)) ;
    new_node->data = val;
    if(!new_node) return ;
    if (q->head == NULL) {
        // Empty queue: head AND tail point to the new node
        q->head = new_node;
        q->tail = new_node;
    } else {
        // Non-empty: attach to tail, then update tail
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->node_count++;
}
int queue_front(queue * q){
    if(q->node_count == 0) return -1;
    else return q->head->data;
}
void queue_pop(queue * q){
    if(q->node_count == 0) return ;
    else {
        Node * trash = q->head;
        q->head = q->head->next;
        free(trash);
        q->node_count--;
        if(q->node_count == 0){
            q->head = NULL;
            q->tail = NULL;
        }
    }
}

int queue_empty(queue * q){
    if(q->node_count == 0) return 1;
    else return 0;
}

int main (){
    printf("the code works at least \n");
    queue * new_q = queue_init();
    if(new_q) printf("the queue is created succesfully \n");
    stack * new_stk = stk_init();
    if(new_stk) printf("the stack is created succesfully ");

    return 0;
}