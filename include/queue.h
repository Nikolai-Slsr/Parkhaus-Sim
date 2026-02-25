#ifndef QUEUE_H
#define QUEUE_H

#include "vehicle.h"

/* queue.h

struct queue:
* first_node: (*node) pointer to the first node in the queue
* last_node: (*node) additional pointer to the last node(by extention the car) in the queue to make adding cars more efficient {O(1) instead of O(n)}
* size: (int) store the number of cars in the queue because this information is accessed often

struct node:
* vehicle: (*vehicle) pointer to the vehicle stored in this node
* next: (*node) pointer to the next node in the queue

*/

/**
 * @brief Initializes an empty queue.
 *
 * This function initializes an empty queue and returns a pointer to it.
 *
 * 
 * @return            A pointer to the initialized queue.
 */
struct queue init();

/**
 * @brief Adds a vehicle to the end of the queue.
 *
 * Adds a vehicle with the specified parameters to the end of the specified queue and returns 1 if successful, 0 if failed.
 * 
 * This function doesn't accept a vehicle struct directly, to have more control over memory management and to avoid potential issues with incorrectly (not stored in the Heap) initialized vehicle structs being passed to the function.
 * Instead, it creates a new vehicle struct internally and adds it to the queue.
 *
 * @param[out] queue  A pointer to the queue to which the vehicle will be added.
 * @param[in] id     The ID of the vehicle to be added.
 * @param[in] parking_time The parking time of the vehicle to be added.
 * @param[in] current_time The current time when the vehicle is added to the queue.
 * @return            Explanation of return value
 */
int enqueue(struct queue *queue, int id, int parking_time, int current_time);

/**
 * @brief Removes the first node(vehicele) from the queue.
 *
 *
 * @param[out]  queue  A pointer to the queue from which the vehicle will be removed.
 * 
 * @return             returns 1 if a car was removed and 0 if the specified queue was empty
 */
int dequeue(struct queue *queue);

/**
 * @brief Prints the queue for debugging purposes.
 *
 *
 * @param[in]  queue  A pointer to the queue to be printed.
 * 
 * @return             returns 1 if a car was removed and 0 if the specified queue was empty
 */
int print_queue(struct queue *queue);

/**
 * @brief Frees all memory allocated for the queue and its vehicles.
 *
 * Uses a double pointer to set the original queue pointer to NULL after freeing the memory,
 * to avoid potential issues with dangling pointers.
 * 
 * @param[out]  queue  A double pointer to the queue to be freed (will be changed to NULL after freeing the memory).
 * 
 * 
 * @return             returns 1 if successful, 0 if the queue was already NULL
 */
int free_queue(struct queue **queue);

//(getLength wird nicht benötigt, da die Länge der Queue in der Queue-Struktur gespeichert wird; somit ist die Laufzeit O(1) anstatt O(n) wie bei einer Implementierung ohne size-Variable)

#endif /* QUEUE_H */