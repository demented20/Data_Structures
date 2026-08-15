# C Data Structures Library

A self-contained, single-file C library implementing fundamental data structures from scratch : no external dependencies, just standard C.

- **Vector (Dynamic Array)** : resizable contiguous array, O(1) amortized push/pop, O(n) deletion by swap-with-last
- **Stack** : LIFO container backed by a singly linked list
- **Queue** : FIFO container backed by a singly linked list with head/tail pointers
- **Hashmap** : separate-chaining hash table with integer keys and values
- **Binary Heap** : min-heap and max-heap built on top of the vector, with heapify and heapsort

## Clone, Build, and Test

The library is single-file (one `.c` and one `.h`).

```bash
# Clone the repository
git clone https://github.com/demented20/Data_Structures.git

# Enter the project directory
cd Data_Structures

# Compile and run the included test suite
gcc -g -Wall -Wextra -Werror data_structures.c -o test
./test
```

Expected output : all tests pass, ending with:

```
========== ALL TESTS PASSED! ==========
```

## ⚠️ Important: Reassign Pointers After Push

Any function that may reallocate memory (`vector_push`, `min_heap_push`, `max_heap_push`, etc.) **returns a new pointer**. Always reassign the result back to your variable : the old pointer may be dangling after the call:

```c
Header *vec = vector_init(4);
vec = vector_push(vec, 10);   // always reassign : vec may have moved
vec = vector_push(vec, 20);
```

Forgetting to reassign is the most common source of bugs when using this library.

## Library Structure

### 1. Vector (Dynamic Array)

```c
typedef struct Header {
    int *items;      // pointer to the first element
    int capacity;    // maximum number of elements that can be stored
    int count;       // current number of elements
} Header;
```

| Function | Description |
|---|---|
| `Header *vector_init(int init_capacity)` | Allocate and initialize a vector |
| `Header *vector_push(Header *vec, int element)` | Append element, reallocating if needed; returns new pointer |
| `void vector_pop(Header *vec)` | Remove the last element (does not return it) |
| `int vector_get(Header *vec, int index)` | Return element at given index (0-based) |
| `int get_length(Header *vec)` | Return current element count |
| `int get_capacity(Header *vec)` | Return current capacity |
| `Header *vector_delete_element(Header *vec, int element)` | Delete first occurrence by swapping with the last element (O(1) average) |
| `void free_the_vector(Header *vec)` | Free the entire vector |

Capacity doubles automatically when full. Optional shrinking is available when `FREE_UNNECESSARY_CAPACITY` is defined.

### 2. Stack (LIFO)

```c
typedef struct stack {
    Node *head;
    int node_count;
} stack;
```

| Function | Description |
|---|---|
| `stack *stk_init()` | Create an empty stack |
| `void stk_push(stack *s, int val)` | Push element onto the stack |
| `void stk_pop(stack *s)` | Remove and discard the top element |
| `int stk_top(stack *s)` | Return the top element without removing it |
| `int stk_empty(stack *s)` | Return 1 if empty, 0 otherwise |
| `int stk_size(stack *s)` | Return the number of elements |

### 3. Queue (FIFO)

```c
typedef struct queue {
    Node *head, *tail;
    int node_count;
} queue;
```

| Function | Description |
|---|---|
| `queue *queue_init()` | Create an empty queue |
| `void queue_push(queue *q, int val)` | Enqueue element at the tail |
| `void queue_pop(queue *q)` | Dequeue and discard the head element |
| `int queue_front(queue *q)` | Return the head element without removing it |
| `int queue_empty(queue *q)` | Return 1 if empty, 0 otherwise |
| `int queue_size(queue *q)` | Return the number of elements |

### 4. Hashmap (Chaining)

```c
typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct Bucket {
    HashNode *head;
    int node_count;
    int bucket_index;
} Bucket;

typedef struct HashmapHeader {
    Bucket *buckets;   // pointer to the first bucket (contiguous array)
    int capacity;      // number of buckets
} HashmapHeader;
```

| Function | Description |
|---|---|
| `HashmapHeader *hashMap_init(int initial_buckets)` | Allocate and initialize hashmap |
| `int hashMap_insert(HashmapHeader *map, int key, int val)` | Insert or update a key-value pair |
| `int hashMap_get(HashmapHeader *map, const int key)` | Retrieve value by key, or -1 if not found |
| `int hashMap_exists(HashmapHeader *map, const int key)` | Return 1 if key exists, 0 otherwise |
| `void hashmap_remove(HashmapHeader *map, const int key)` | Delete the key-value pair |
| `void hashMap_destroy(HashmapHeader *map)` | Free all memory |

Hash function (customizable : replace with a stronger hash for production):

```c
int hash_function(int key, int bucket_count) {
    return key % bucket_count;
}
```

### 5. Binary Heap / Priority Queue (Min/Max)

Heaps use the same `Header` struct as the vector, storing integers while maintaining the heap property. A `HeapType` enum (`HEAP_MIN` / `HEAP_MAX`) lets you treat the heap as a generic priority queue without picking min or max functions by hand.

| Function | Description |
|---|---|
| `Header *min_heap_init(int capacity)` / `max_heap_init(int capacity)` | Create an empty heap |
| `Header *p_queue_init(int capacity, HeapType type)` | Create an empty priority queue : dispatches to `min_heap_init` or `max_heap_init` based on `type` |
| `Header *min_heap_push(Header *heap, int element)` / `max_heap_push(...)` | Insert an element and bubble up : **returns new pointer** |
| `int min_heap_pop(Header *heap)` / `max_heap_pop(Header *heap)` | Remove and return the root (min or max) |
| `int min_peek(Header *heap)` / `max_peek(Header *heap)` | Return the root without removing it |
| `void min_heapify(Header *heap)` / `max_heapify(Header *heap)` | Build a heap from an arbitrary array in O(n) |
| `Header *vector_to_minheap(Header *vec)` / `vector_to_maxheap(...)` | Convert an existing vector into a heap (copies data) |
| `Header *vector_to_pqueue(Header *vec, HeapType type)` | Convert an existing vector into a priority queue : dispatches to `vector_to_minheap` or `vector_to_maxheap` based on `type` |
| `void heapsort(Header *vec, SortType type)` | Sort the vector in-place using heap sort. `type` is `Increasing` or `Decreasing` |
| `void heap_destroy(Header *heap)` | Free the heap |

There is no separate priority-queue struct : `p_queue_init` and `vector_to_pqueue` are convenience wrappers around the min/max heap, selected at call time via `HeapType`:

```c
typedef enum { HEAP_MIN, HEAP_MAX } HeapType;

Header *pq = p_queue_init(8, HEAP_MAX);   // allocates exactly like max_heap_init(8)
pq = max_heap_push(pq, 42);               // you still call the matching max_/min_ functions on it :
                                           // HeapType only picks which init/convert function runs
```

Internal helpers (iterative, not recursive, to avoid stack overflow): `sift_up_min`, `sift_down_min`, `sift_up_max`, `sift_down_max`, `swap`.

**Enums used by the heap/priority-queue API:**

```c
typedef enum { HEAP_MIN, HEAP_MAX } HeapType;      // used by p_queue_init, vector_to_pqueue
typedef enum { Increasing, Decreasing } SortType;   // used by heapsort
```

## Key Design Decisions

- **Single allocation for Header + data** : both the vector/heap header and the hashmap's bucket array are allocated in one contiguous block for cache locality and simpler cleanup.
- **Reallocated pointers are returned** : functions that may reallocate (`vector_push`, heap pushes) return the new `Header*`; callers must reassign to avoid dangling pointers (see warning above).
- **Error handling via sentinels** : functions return `-1` or `NULL` on failure; `-1` also signals "not found," so the library assumes `-1` is never a valid stored value.
- **Hashmap chaining** : separate chaining with linked lists; inserts go at the head (O(1)) after a duplicate check.
- **Iterative heap sifts** : no recursion, avoiding stack overflow on large heaps.

## Test Coverage

- **Vector** : init, push, pop, get, delete, reallocation, capacity growth
- **Stack** : all LIFO operations
- **Queue** : all FIFO operations
- **Hashmap** : insert, update, lookup, exists, remove, destroy
- **Min-heap** : push, pop, peek, heap property verification
- **Max-heap** : push, pop, peek, heap property verification
- **Heapify** : building heaps from vectors
- **Heapsort** : sorting in both increasing and decreasing order

## Why This Library?

- No external dependencies : just standard C
- Clear, consistent API following `init` / `push` / `pop` / `destroy` naming conventions
- Memory-safe : every allocation has a matching free
- Educational : a solid reference for how classic data structures work under the hood

## Contributing

Contributions are welcome! If you'd like to help out:

1. Fork the repository and create a feature branch.
2. Make your changes, keeping the existing naming conventions (`init`, `push`, `pop`, `destroy`, etc.).
3. Add or update tests so `./test` still ends with `ALL TESTS PASSED!`.
4. Open a pull request describing the change and why it's useful.

Bug reports and suggestions are just as welcome as code : feel free to open an issue.

## License

This project was developed for educational and demonstration purposes, as well as for community use and contribution. See [LICENSE](LICENSE) for details, or open an issue if you'd like clarification on usage terms.

## Author

**Madani Alaoui Youness** : [@demented20](https://github.com/demented20)
