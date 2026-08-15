#ifndef DATA_STRUCTURES__H
#define DATA_STRUCTURES__H

#define INIT_CAPACITY 256 // made for initializing the vectors
#define MIN_CAPACITY 32 // the minimum size for the array not to go under
#define MAP_INIT_BUCKETS 4  // the initial buckets number to start the hashmap with

typedef struct Node {
    int data;
    struct Node* next;
} Node;

//Member Methods :
Node* list_push_front(Node* head,int val);

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
Header* vector_push(Header *pointer_to_header , int element_tobe_pushed);
void vector_pop(Header* vec);
int vector_get(Header* vec, int index); 
int get_length(Header * meta_data);
int get_capacity(Header *meta_data);
Header* vector_delete_element(Header* meta_data,int element); 
void free_the_vector(Header* meta_data);
//Hashmap node structure
typedef struct HashNode
{
    int key;
    int value;
    struct HashNode * next;
}HashNode;

typedef struct Bucket
{
    HashNode * head;
    int node_count;
    int bucket_index;
}Bucket;
typedef struct HashmapHeader
{
    Bucket *buckets; // this is pointer to the first bucket
    int capacity; // this is number of buckets the vector stores
}HashmapHeader;

static HashNode * init_node0(HashNode * node);
HashNode * init_node(HashNode * node , int key , int value);
//Member Methods :
HashmapHeader * hashMap_init(int initial_buckets);
int hashMap_insert(HashmapHeader* hashmap, int key , int val);
int hashMap_get(HashmapHeader * hashmap, const int key);
int hashMap_exists(HashmapHeader * hashmap, const int key);
void hashmap_remove(HashmapHeader * hashmap, const int key);
void hashMap_destroy(HashmapHeader * hashmap);

//DEFINE THE HASH FUNCTION :
int hash_function(int key,int buckets_count);

//Making the necessary stuctures and methods for the Heap (min/max)

typedef enum {
    HEAP_MIN,
    HEAP_MAX
} HeapType;

Header * min_heap_init(int capacity);
Header * max_heap_init(int capacity);
//now we add the function to init a p_queue
Header * pqueue_init(int capacity , HeapType type);

Header * vector_to_minheap(Header * vector);
Header * vector_to_maxheap(Header * vector);
//now we add the function to make a p_queue from a vector
Header * vector_to_pqueue(Header* vector , HeapType type);

Header* min_heap_push(Header * minheap , int element);
Header* max_heap_push(Header * maxheap , int element);

void min_heapify(Header * minheap);
void max_heapify(Header * maxheap);

int min_heap_pop(Header * minheap);
int max_heap_pop(Header * maxheap);

int max_peek(Header * maxheap);
int min_peek(Header * minheap);

void heap_destroy(Header * heap);



//we implement helper functions :
void swap(Header * heap ,int idx_1 ,int idx_2);
void sift_up_min(Header* heap, int index);
void sift_down_min(Header* heap, int index);
void sift_up_max(Header* heap, int index);
void sift_down_max(Header* heap, int index);
//we might add heap sort 
typedef enum
{
    Increasing,
    Decreasing
}SortType;

void heapsort(Header * vector_to_be_sorted,SortType type);

#endif