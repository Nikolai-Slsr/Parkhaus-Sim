/* queue.h

struct queue:
* first_node: (*node) pointer to the first node in the queue
* last_node: (*node) additional pointer to the last node(by extention the car) in the queue to make adding cars more efficient {O(1) instead of O(n)}
* size: (int) store the number of cars in the queue because this information is accessed often

struct node:
* vehicle: (*vehicle) pointer to the vehicle stored in this node
* next: (*node) pointer to the next node in the queue

queue init() returns an empty queue

int enqueue(*queue queue, int id, int parking_time, int current_time) adds a vehicle(with the specified parameters) 
    to the end of the specified queue and returns 1 if successful, 0 if failed
    This function doesn't accept a vehicle struct directly, to have more control over memory management and to avoid potential issues with incorrectly (not stored in the Heap) initialized vehicle structs being passed to the function.
    Instead, it creates a new vehicle struct internally and adds it to the queue.

int dequeue(*queue) removes the first vehicle, returns 1 if a car was removed and 0 if the specified queue was empty

int print_queue(*queue, int current_time) prints the queue for debugging purposes; returns 1 if successful, 0 if empty

int free_queue(**queue) frees all memory allocated for the queue and its vehicles; returns 1 if successful, 0 if the queue was already empty
    uses a double pointer to set the original queue pointer to NULL after freeing the memory, to avoid potential issues with dangling pointers

(getLength wird nicht benötigt, da die Länge der Queue in der Queue-Struktur gespeichert wird; somit ist die Laufzeit O(1) anstatt O(n) wie bei einer Implementierung ohne size-Variable)
*/