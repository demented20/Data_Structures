#include "data_structures.h"
#include<stdlib.h>
#include <stdio.h>
//this is for testing this code :
#include <assert.h>
// YOU CAN ENABLE THE AUTOMATIC VECTOR RESIZE FEATURE BY UNCOMMENTING THE NEXT COMMAND 
//#define FREE_UNNECESSARY_CAPACITY





// int linked list definition 

Node* list_push_front(Node* head,int val){
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
    if(!new_data) return;
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
    if(stk->node_count == 0) return -1;//to indicate the failure of finding an element on top
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
    if(!new_node) return ;
    new_node->data = val;
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
    if(q->node_count == 0) return -1;//empty queue
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
    pointer_to_header->items[pointer_to_header->count++] = element_tobe_pushed;
    return pointer_to_header;
} 

void vector_pop(Header* vec) {
    if (!vec || vec->count == 0) {
        return ; 
    }
    int last = vec->items[vec->count - 1];
    vec->count--;
}

int vector_get(Header* vec, int index) {
    if (!vec || index < 0 || index >= vec->count) {
        return -1;  // for invalid index or vector
    }
    return vec->items[index];
}

int get_length(Header* meta_data){
        if (meta_data == NULL) return -1 ;//for failure 
        return meta_data->count;
}

int get_capacity(Header * meta_data){
        if (meta_data == NULL) return -1;//for failure 
        return meta_data->capacity;
}

void free_the_vector(Header *meta_data){
        if (meta_data ==NULL) return;
        free(meta_data);
}

Header* vector_delete_element(Header* meta_data,int element){
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
//DEFINE THE HASH FUNCTION :
//this is a simple one that works well for easy usages and tests 
//dealing with collisions requires a better algorithm 
int hash_function(int key, int bucket_count){
    int hash = key%bucket_count;// DEFINE THE HASHING ALGORITHM TO BE COMPATIBLE WITH YOUR BUCKETS
                     // currently the hashmap works with hashfunctions using modulo % 
    return hash;
}

HashNode * init_node0(HashNode * node){
    node->key = 0 ;
    node->value = 0;
    node->next = NULL;
    return node;
}

HashNode * init_node(HashNode * node , int key , int value){
    node->key = key ;
    node->value = value;
    node->next = NULL;
    return node;
}
//
HashmapHeader * hashMap_init(int initial_buckets){
    if(initial_buckets<=0) initial_buckets = MAP_INIT_BUCKETS;
    HashmapHeader * mapHeader = malloc (sizeof(HashmapHeader) + initial_buckets * sizeof(Bucket));
    if(mapHeader == NULL) return NULL; // allocation failed 
    mapHeader->buckets = (Bucket*)(mapHeader+1);
    mapHeader->capacity = initial_buckets;
    for(size_t i = 0 ; i<initial_buckets;++i){ // initialize the buckets
        (mapHeader->buckets+i)->bucket_index = i;
        (mapHeader->buckets+i)->node_count =0;
        (mapHeader->buckets+i)->head = NULL;
    }
    return mapHeader;
}

int hashMap_insert(HashmapHeader* hashmap, int key , int val){
    int hash = hash_function(key,hashmap->capacity);
    Bucket * this_bucket = hashmap->buckets+hash;
    //we need to check if the key exists or not to know if we either have to update the value or create a new node to store the pair 
    HashNode* tmp = this_bucket->head;
    while (tmp) {
        if (tmp->key == key) {
            tmp->value = val;  
            return 0;//updated successfully     
        }
        tmp = tmp->next;
    }
    if(this_bucket->node_count == 0){// we need to make a new head and store the pointer to it 
        HashNode * new_head = malloc(sizeof(HashNode));
        if(new_head == NULL) return -1;// malloc failed
        this_bucket->head = init_node(new_head,key,val);
        this_bucket->node_count ++;
        return 0;
    }else{ // we already have a head and we need to append to it 
        HashNode * node = malloc(sizeof(HashNode));
        if(node == NULL) return -1;// malloc failed
        init_node(node,key,val);
        node->next = this_bucket->head;
        this_bucket->head = node;
        this_bucket->node_count++; // this is o(1)insertion better than inserting at the tail
        return 0;
    }
}

int hashMap_get(HashmapHeader * hashmap, const int key){
    int hash = hash_function(key,hashmap->capacity);
    Bucket * this_bucket = hashmap->buckets+hash;
    if(this_bucket->node_count == 0) return -1;//the bucket is empty so element not found
    else {
        HashNode * tmp = this_bucket->head;
        int found = -1;
        while(tmp!= NULL ){
            if(tmp->key == key) {
                found = tmp->value;
                break;
            }
            else tmp = tmp->next;
        }
        return found;
    }
}
int hashMap_exists(HashmapHeader * hashmap, const int key){//boolean simulation
    int hash = hash_function(key,hashmap->capacity);
    Bucket* bucket = hashmap->buckets + hash;
    HashNode* tmp = bucket->head;
    while (tmp) {
        if (tmp->key == key) return 1;// for true
        tmp = tmp->next;
    }
    return 0;//for false
} 

void hashmap_remove(HashmapHeader * hashmap, const int key){
    int hash = hash_function(key,hashmap->capacity);
    Bucket * this_bucket = hashmap->buckets+hash;
    if(this_bucket->node_count == 0) return ;//the bucket is empty so cant delete
    HashNode* tmp = this_bucket->head;
    HashNode* prev = NULL;
    while (tmp) {
        if (tmp->key == key) {//found our target
            if (prev) { //we check if we can link to the previous node aka if its the head or an other node
                prev->next = tmp->next;
            } else {//if we cant we make the next node our new head because we need to delete the head
                this_bucket->head = tmp->next;
            }
            free(tmp);
            this_bucket->node_count--;
            return; 
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void hashMap_destroy(HashmapHeader * hashmap){
    if(hashmap == NULL) return;
    //we need to free every instance one by one :
    //starting by the hashnodes , then the buckets , then the map vector
    for(int i = hashmap->capacity-1 ; i>=0 ; i--){
        if ((hashmap->buckets+i)->head == 0) goto skip;
        else {
            HashNode *tmp = (hashmap->buckets+i)->head;
            while (tmp != NULL){
                HashNode * save_next = tmp->next;
                free(tmp);
                tmp = save_next;
            } 
        }
    skip:
    }
    free(hashmap);
}
//implementation of the Heap methods :
Header * min_heap_init(int capacity){
    if(capacity <=0) capacity = MIN_CAPACITY;
    Header * new_heap  = malloc(sizeof(Header)+sizeof(int)* capacity);
    if(new_heap == NULL) return NULL; //allocation failed 
    new_heap->items = (int*)(new_heap+1);
    new_heap->capacity = capacity;
    new_heap->count = 0;
    return new_heap;
}

Header * max_heap_init(int capacity){
    if(capacity <=0) capacity = MIN_CAPACITY;
    Header * new_heap  = malloc(sizeof(Header)+sizeof(int)* capacity);
    if(new_heap == NULL) return NULL; //allocation failed 
    new_heap->items = (int*)(new_heap+1);
    new_heap->capacity = capacity;
    new_heap->count = 0;
    return new_heap;
}

Header * p_queue_init(int capacity , HeapType type){
    if(type == HEAP_MAX) return max_heap_init(capacity);
    else if(type == HEAP_MIN) return min_heap_init(capacity);
    else return NULL;
}


Header* min_heap_push(Header * minheap , int element){
    if(minheap == NULL) return NULL;
    minheap = vector_push(minheap,element);
    if(minheap)sift_up_min(minheap, minheap->count - 1);// if the pointer is valid or the reallocation is successful then we call the sifting function
    return minheap;
}

Header* max_heap_push(Header * maxheap , int element){
    if(maxheap == NULL) return NULL;
    maxheap = vector_push(maxheap,element);
    if(maxheap) sift_up_max(maxheap, maxheap->count - 1);// if the pointer is valid or the reallocation is successful then we call the sifting function
    return maxheap;
}

int min_peek(Header * minheap){
    if(!minheap||minheap->count == 0) return -1;
    return *minheap->items;
}

int max_peek(Header * maxheap){
    if(!maxheap||maxheap->count == 0) return -1;
    return *maxheap->items;
}

void swap(Header * heap , int idx_1 ,int idx_2 ){
    int temp = heap->items[idx_1] ;
    heap->items[idx_1] = heap->items[idx_2];
    heap->items[idx_2] = temp;
}

void heap_destroy(Header * heap){
    if(heap== NULL) return;//nothing to free
    free(heap);
}

int min_heap_pop(Header * minheap){
    if(!minheap || minheap->count == 0) return -1;
    int toreturn = min_peek(minheap);
    minheap->items[0] = minheap->items[minheap->count-1];
    minheap->count--;
    sift_down_min(minheap, 0);
    return toreturn;
}

int max_heap_pop(Header * maxheap){
    if(!maxheap || maxheap->count == 0) return -1;
    int toreturn = max_peek(maxheap);
    maxheap->items[0] = maxheap->items[maxheap->count-1];
    maxheap->count--;
    sift_down_max(maxheap, 0);
    return toreturn; 
}
//////////////////////////////////////////////////////////////////////////////////////////
void sift_up_min(Header* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->items[index] < heap->items[parent]) {
            swap(heap, index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

void sift_down_min(Header* heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap->count && heap->items[left] < heap->items[smallest])
            smallest = left;
        if (right < heap->count && heap->items[right] < heap->items[smallest])
            smallest = right;

        if (smallest == index)
            break;

        swap(heap, index, smallest);
        index = smallest;
    }
}

void sift_up_max(Header* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->items[index] > heap->items[parent]) {
            swap(heap, index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

void sift_down_max(Header* heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap->count && heap->items[left] > heap->items[largest])
            largest = left;
        if (right < heap->count && heap->items[right] > heap->items[largest])
            largest = right;

        if (largest == index)
            break;

        swap(heap, index, largest);
        index = largest;
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void min_heapify(Header* minheap) {
    if (!minheap || minheap->count <= 1) return;

    // Start from the last non-leaf node and sift down each
    for (int i = minheap->count / 2 - 1; i >= 0; i--) {
        sift_down_min(minheap, i);
    }
}

void max_heapify(Header* maxheap) {
    if (!maxheap || maxheap->count <= 1) return;

    for (int i = maxheap->count / 2 - 1; i >= 0; i--) {
        sift_down_max(maxheap, i);
    }
}

Header * vector_to_minheap(Header * vector){
    if(!vector || vector->count == 0) return NULL;
    Header * new_heap = min_heap_init(vector->count);
    for (int i = 0 ; i < vector->count;i++){
        new_heap->items[i] = vector->items[i];
    }
    new_heap->count = vector->count;
    min_heapify(new_heap);
    return new_heap;
}

Header * vector_to_maxheap(Header * vector){
    if(!vector || vector->count == 0) return NULL;
    Header * new_heap = max_heap_init(vector->count);
    for (int i = 0 ; i < vector->count;i++){
        new_heap->items[i] = vector->items[i];
    }
    new_heap->count = vector->count;
    max_heapify(new_heap);
    return new_heap;
}

Header * vector_to_pqueue(Header* vector , HeapType type){
    if(type == HEAP_MAX) return vector_to_maxheap(vector);
    else if(type == HEAP_MIN) return vector_to_minheap(vector);
    else return NULL; // we dont know which type of pqueue
}

void heapsort(Header * vector , SortType type){
    if (!vector || vector->count == 0) return;
    HeapType new_type = HEAP_MAX;
    if(type == Decreasing)  new_type = HEAP_MIN;
    Header * heap = vector_to_pqueue(vector,new_type);
    if (!heap) return;//we were not able to build the heap
    for (int i = vector->count - 1; i >= 0; i--) {
        int popped;
        if (new_type == HEAP_MAX) {
            popped = max_heap_pop(heap);
        } else {
            popped = min_heap_pop(heap);
        }
        vector->items[i] = popped;
    }
    heap_destroy(heap);
}
/////////////////////////////////////////////////////////////////////////////////////////////////

// Print a vector for debugging
void print_vector(Header* vec, const char* label) {
    if (!vec) {
        printf("%s: NULL\n", label);
        return;
    }
    printf("%s: [", label);
    for (int i = 0; i < vec->count; i++) {
        printf("%d", vec->items[i]);
        if (i < vec->count - 1) printf(", ");
    }
    printf("] (size=%d, cap=%d)\n", vec->count, vec->capacity);
}

// Print a hashmap (debug helper)
void print_hashmap(HashmapHeader* map) {
    if (!map) {
        printf("Hashmap: NULL\n");
        return;
    }
    printf("Hashmap (capacity=%d):\n", map->capacity);
    for (int i = 0; i < map->capacity; i++) {
        Bucket* b = map->buckets + i;
        if (b->node_count == 0) continue;
        printf("  Bucket %d (count=%d): ", i, b->node_count);
        HashNode* tmp = b->head;
        while (tmp) {
            printf("(%d -> %d) ", tmp->key, tmp->value);
            tmp = tmp->next;
        }
        printf("\n");
    }
}
//to test the code remove the number "2" written after main the compile and run the program
int main2() {
    printf("========== DATA STRUCTURES TEST SUITE ==========\n\n");
    printf("COMPILED SUCCESSFULLYy\n");

    // =====================================================
    // 1. VECTOR TESTS
    // =====================================================
    printf("1. VECTOR TESTS\n");
    printf("---------------\n");

    Header* vec = vector_init(4);
    assert(vec != NULL);
    assert(vec->count == 0);
    printf(" Vector initialized\n");

    // Push elements
    vec = vector_push(vec, 10);
    vec = vector_push(vec, 20);
    vec = vector_push(vec, 30);
    vec = vector_push(vec, 40);
    vec = vector_push(vec, 50);  // Should trigger reallocation
    assert(vec->count == 5);
    assert(get_length(vec) == 5);
    assert(get_capacity(vec) >= 8);
    printf(" Pushed 5 elements, count=%d, cap=%d\n", vec->count, vec->capacity);

    // Get elements
    assert(vector_get(vec, 0) == 10);
    assert(vector_get(vec, 2) == 30);
    assert(vector_get(vec, 4) == 50);
    assert(vector_get(vec, 5) == -1);  // Out of bounds
    printf(" Vector get works\n");

    // Pop elements
    vector_pop(vec);  // Removes 50
    assert(vec->count == 4);
    assert(vector_get(vec, 3) == 40);
    printf(" Vector pop works\n");

    // Delete element
    vec = vector_delete_element(vec, 20);
    assert(vec->count == 3);
    assert(vector_get(vec, 0) == 10);
    assert(vector_get(vec, 1) == 40);
    assert(vector_get(vec, 2) == 30);
    printf(" Vector delete works\n");

    print_vector(vec, "Final vector");

    // =====================================================
    // 2. STACK TESTS
    // =====================================================
    printf("\n2. STACK TESTS\n");
    printf("--------------\n");

    stack* stk = stk_init();
    assert(stk != NULL);
    assert(stk_empty(stk) == 1);

    stk_push(stk, 10);
    stk_push(stk, 20);
    stk_push(stk, 30);
    assert(stk_size(stk) == 3);
    assert(stk_top(stk) == 30);

    stk_pop(stk);
    assert(stk_top(stk) == 20);
    assert(stk_size(stk) == 2);

    stk_pop(stk);
    stk_pop(stk);
    assert(stk_empty(stk) == 1);
    printf(" Stack operations passed\n");

    free(stk);

    // =====================================================
    // 3. QUEUE TESTS
    // =====================================================
    printf("\n3. QUEUE TESTS\n");
    printf("--------------\n");

    queue* q = queue_init();
    assert(q != NULL);
    assert(queue_empty(q) == 1);

    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 30);
    assert(queue_size(q) == 3);
    assert(queue_front(q) == 10);

    queue_pop(q);
    assert(queue_front(q) == 20);
    assert(queue_size(q) == 2);

    queue_pop(q);
    queue_pop(q);
    assert(queue_empty(q) == 1);
    printf(" Queue operations passed\n");

    free(q);

    // =====================================================
    // 4. HASHMAP TESTS
    // =====================================================
    printf("\n4. HASHMAP TESTS\n");
    printf("---------------\n");

    HashmapHeader* map = hashMap_init(4);
    assert(map != NULL);
    assert(map->capacity == 4);

    // Insert entries
    assert(hashMap_insert(map, 5, 100) == 0);
    assert(hashMap_insert(map, 15, 200) == 0);  // Same bucket (5 % 4 == 15 % 4)
    assert(hashMap_insert(map, 25, 300) == 0);  // Same bucket
    assert(hashMap_insert(map, 7, 400) == 0);

    // Check existence
    assert(hashMap_exists(map, 5) == 1);
    assert(hashMap_exists(map, 99) == 0);

    // Get values
    assert(hashMap_get(map, 5) == 100);
    assert(hashMap_get(map, 15) == 200);
    assert(hashMap_get(map, 25) == 300);
    assert(hashMap_get(map, 7) == 400);
    assert(hashMap_get(map, 999) == -1);
    printf(" Hashmap insert/get/exists passed\n");

    // Update existing key
    assert(hashMap_insert(map, 5, 999) == 0);
    assert(hashMap_get(map, 5) == 999);
    printf(" Hashmap update works\n");

    // Remove
    hashmap_remove(map, 15);
    assert(hashMap_exists(map, 15) == 0);
    assert(hashMap_get(map, 15) == -1);
    hashmap_remove(map, 5);
    assert(hashMap_exists(map, 5) == 0);
    printf(" Hashmap remove works\n");

    print_hashmap(map);

    // =====================================================
    // 5. HEAP TESTS
    // =====================================================
    printf("\n5. HEAP TESTS\n");
    printf("-------------\n");

    // Min-heap
    Header* minheap = min_heap_init(4);
    minheap = min_heap_push(minheap, 5);
    minheap = min_heap_push(minheap, 2);
    minheap = min_heap_push(minheap, 8);
    minheap = min_heap_push(minheap, 1);
    minheap = min_heap_push(minheap, 3);

    assert(min_peek(minheap) == 1);
    assert(min_heap_pop(minheap) == 1);
    assert(min_peek(minheap) == 2);
    assert(min_heap_pop(minheap) == 2);
    /*here
    printf("Heap contents: ");
    for (int i = 0; i < minheap->count; i++) {
        printf("%d ", minheap->items[i]);
    }
    printf("\n");
    assert(min_heap_pop(minheap) == 3);
    here*/
    assert(min_heap_pop(minheap) == 3);
    assert(min_heap_pop(minheap) == 5);
    assert(min_heap_pop(minheap) == 8);
    printf(" Min-heap passed\n");

    heap_destroy(minheap);

    // Max-heap
    Header* maxheap = max_heap_init(4);
    maxheap = max_heap_push(maxheap, 5);
    maxheap = max_heap_push(maxheap, 2);
    maxheap = max_heap_push(maxheap, 8);
    maxheap = max_heap_push(maxheap, 1);
    maxheap = max_heap_push(maxheap, 3);

    assert(max_peek(maxheap) == 8);
    assert(max_heap_pop(maxheap) == 8);
    assert(max_peek(maxheap) == 5);
    assert(max_heap_pop(maxheap) == 5);
    assert(max_heap_pop(maxheap) == 3);
    assert(max_heap_pop(maxheap) == 2);
    assert(max_heap_pop(maxheap) == 1);
    printf(" Max-heap passed\n");

    heap_destroy(maxheap);

    // =====================================================
    // 6. HEAPIFY & VECTOR-TO-HEAP TESTS
    // =====================================================
    printf("\n6. HEAPIFY TESTS\n");
    printf("----------------\n");

    Header* raw = vector_init(6);
    vector_push(raw, 5);
    vector_push(raw, 3);
    vector_push(raw, 8);
    vector_push(raw, 1);
    vector_push(raw, 9);
    vector_push(raw, 2);
    print_vector(raw, "Raw vector");

    Header* minheap2 = vector_to_minheap(raw);
    assert(minheap2 != NULL);
    assert(minheap2->count == 6);
    assert(min_peek(minheap2) == 1);
    printf(" Vector to min-heap: min=%d\n", min_peek(minheap2));
    print_vector(minheap2, "Min-heap");

    Header* maxheap2 = vector_to_maxheap(raw);
    assert(maxheap2 != NULL);
    assert(maxheap2->count == 6);
    assert(max_peek(maxheap2) == 9);
    printf(" Vector to max-heap: max=%d\n", max_peek(maxheap2));
    print_vector(maxheap2, "Max-heap");

    heap_destroy(minheap2);
    heap_destroy(maxheap2);
    free_the_vector(raw);

    // =====================================================
    // 7. HEAPSORT TESTS
    // =====================================================
    printf("\n7. HEAPSORT TESTS\n");
    printf("-----------------\n");

    Header* sort_vec = vector_init(6);
    vector_push(sort_vec, 5);
    vector_push(sort_vec, 3);
    vector_push(sort_vec, 8);
    vector_push(sort_vec, 1);
    vector_push(sort_vec, 9);
    vector_push(sort_vec, 2);
    print_vector(sort_vec, "Before sorting");

    heapsort(sort_vec, Increasing);
    print_vector(sort_vec, "After increasing sort");
    for (int i = 0; i < sort_vec->count - 1; i++) {
        assert(sort_vec->items[i] <= sort_vec->items[i + 1]);
    }
    printf(" Increasing order verified\n");

    heapsort(sort_vec, Decreasing);
    print_vector(sort_vec, "After decreasing sort");
    for (int i = 0; i < sort_vec->count - 1; i++) {
        assert(sort_vec->items[i] >= sort_vec->items[i + 1]);
    }
    printf(" Decreasing order verified\n");

    free_the_vector(sort_vec);

    // =====================================================
    // 8. CLEANUP
    // =====================================================
    printf("\n8. CLEANUP\n");
    printf("----------\n");

    hashMap_destroy(map);
    printf(" Hashmap destroyed\n");

    printf("\n========== ALL TESTS PASSED! ==========\n");
    return 0;
}