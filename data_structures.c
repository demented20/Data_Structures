#include "data_structures.h"

#ifndef DATA_STRUCTURES__H
#define DATA_STRUCTURES__H

// YOU CAN ENABLE THE AUTOMATIC VECTOR RESIZE FEATURE BY UNCOMMENTING THE NEXT COMMAND 
//#define FREE_UNNECESSARY_CAPACITY



// int linked list definition 

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
//defining and implementing dynamic array methods 
Header * vector_init(int init_capacity){
    if (init_capacity <= 0)
        init_capacity= MIN_CAPACITY;
    Header * head = malloc(sizeof(Header)+init_capacity* sizeof(int));
    if (head == NULL) return NULL;// failed to init the vector
    head->capacity = init_capacity;
    head->count = 0;
    head->items = (int*)(head+1);
    return head;
}
Header* vector_push(Header *pointer_to_header , int element_tobe_pushed){
    if(pointer_to_header == NULL) return NULL;//either the pointer doesnt exist or the array is un initialized 
    if(pointer_to_header->capacity >= pointer_to_header->count+1) goto directly_push;
    else {
        // we need to realloc anew chunk with more capacity 
        size_t new_capacity = pointer_to_header->capacity * 2;
        Header  *new_header = realloc(pointer_to_header, sizeof(Header) + sizeof(int) * new_capacity);
        if (new_header == NULL) return NULL;// the reallocation failed   
            //we update the meta data       
            new_header->capacity = new_capacity;
            new_header->items= (int*)(new_header+ 1);
            pointer_to_header = new_header;
    }  
    directly_push :
    ((int*)(pointer_to_header+1))[pointer_to_header->count++] = element_tobe_pushed;
    return pointer_to_header;
} 
int get_length(Header* meta_data){
        if (meta_data == NULL) return -1 ;//for failure 
        return meta_data->count;
}
int get_capacity(Header * meta_data){
        if (meta_data == NULL) return -1;//for failure 
        return meta_data->capacity;
}
void free_the_array(Header *meta_data){
        if (meta_data ==NULL) return;
        free(meta_data);
}

Header* array_delete_element(Header* meta_data,int element){
        if (meta_data==NULL) return NULL; //handles invalid pointer 
        if (meta_data->count == 0 ) return meta_data;// handles empty arrays by returning the original empty vector

        int index = -1; //way of simulating the boolean and at the same time returning the index if student id is found found
        for (size_t i = 0; i < meta_data->count; i++){

            if ((meta_data->items)[i] == element){
                index = i;//recording the index of the element we want to delete
                break;
            }
        } 
        if (index == -1) return meta_data;
                //swwapping with the last element
                //its more of a overwrite than a complete swap 
                if (index != meta_data->count - 1) (meta_data->items)[index] = (meta_data->items)[meta_data->count - 1];
                //upadate meta data 
                meta_data->count--;

                //this part of the code is added to shrink if the count of the elements is less than the half of the array capacity
                // this is a good way to keep your memory usage minimal and ur code optimized 
                //it can be omited by undefining or commenting it
                #ifdef FREE_UNNECESSARY_CAPACITY

                if (meta_data->count < (meta_data->capacity / 2) &&( meta_data->capacity > MIN_CAPACITY)){

                    size_t new_capacity =meta_data->capacity / 2;
                    if (new_capacity< MIN_CAPACITY) new_capacity = MIN_CAPACITY;
                    //this allows us to handle the array with few elements ,
                    //because we increase the capacity be x1.5 (and this might cause problems when it comes to 0 and 1 elements and we want to push)
                    //this way we dont allow the array to go bellow 32 elements        
                    //__________________________________________________________________________________________________________________________________
                    
                    //these following lines reallocate memory for an array using the pointer in the parameters and the new size (half of the precious size)
                    Header *new_vector = realloc(meta_data,sizeof(Header) +sizeof(int) *new_capacity);

                    if (new_vector == NULL) return meta_data; //if the operation fails we still have the pointer to the metadata
                    //meta data update
                    new_vector->capacity = new_capacity;
                    new_vector->items = (int*)(new_vector+ 1);
                    return new_vector;
                }
                #endif

            return meta_data;
        
    }

//now the inmplementatios of the min/max heap using our recently created dynamic array or vector 

#endif
int main (){
    printf("the code works at least \n");
    queue * new_q = queue_init();
    if(new_q) printf("the queue is created succesfully \n");
    stack * new_stk = stk_init();
    if(new_stk) printf("the stack is created succesfully ");
    void *newvec = vector_init(256);
    return 0; 
}