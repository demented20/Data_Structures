#include <stdio.h>
#include<stdlib.h>
#define INIT_CAPACITY 256
#define MIN_CAPACITY 32

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
// Queue data structure
typedef struct queue
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
//hashmap data structure
typedef struct Header
{
    int *items; // this is pointer to the first int element 
    int capacity; // this is the max number of integers that the vector can store
    int count ; // this holds the count of the integer elements that are storred in the vector
}Header;
//Member Methods :
Header * vector_init(int init_capacity);
Header* vector_push(int *pointer_to_first_element , int element_tobe_pushed);
int get_length(Header * meta_data);
int get_capacity(Header *meta_data);
Header* vector_delete_element(Header* meta_data,int element); 
void free_the_vector(Header* meta_data);
//Hashmap node structure
typedef struct Bucket
{
    HashNode * head;
    int bucket_index;
}Bucket;
typedef struct HashmapHeader
{
    Bucket *buckets; // this is pointer to the first bucket
    int capacity; // this is the max number of buckets that the vector can store
    int count ; // this holds the count of the buckets that are storred in the vector
}HashmapHeader;
typedef struct HashNode
{
    int key;
    int value;
    HashNode * next;
}HashNode;
//Member Methods :
HashmapHeader * hashMap_init(int initial_buckets);
void hashMap_insert(HashmapHeader* hashmap, int key , int val);
int hashMap_get(HashmapHeader * hashmap, const int key);
int hashMap_exists(HashmapHeader * hashmap, const int key);
void hashmap_remove(HashmapHeader * hashmap, const int key);
void hashMap_destroy(HashmapHeader * hashmap);