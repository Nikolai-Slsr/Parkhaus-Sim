#ifndef QUEUE_H
#define QUEUE_H

#include "vehicle.h"

struct node {
    struct vehicle *vehicle; //pointer to the vehicle stored in this node
    struct node *next; //pointer to the next node in the queue
};

struct queue {
    struct node *first_node; //pointer to the first node in the queue
    struct node *last_node; //additional pointer to the last node(by extention the car) in the queue to make adding cars more efficient {O(1) instead of O(n)}
    int size; //store the number of cars in the queue because this information is accessed often
};

/**
 * @brief Initializes an empty queue.
 *
 * This function initializes an empty queue in the Heap and returns a pointer to it.
 *
 * 
 * @return            A pointer to the initialized queue.
 */
struct queue *init_queue();

/**
 * @brief Adds a vehicle to the end of the queue.
 *
 * Adds a vehicle with the specified parameters to the end of the specified queue and returns 0 if successful, -1 if failed.
 * 
 * This function doesn't accept a vehicle struct directly, to have more control over memory management and to avoid potential issues with incorrectly (not stored in the Heap) initialized vehicle structs being passed to the function.
 * Instead, it creates a new vehicle struct internally and adds it to the queue.
 *
 * @param[in,out] queue         A pointer to the queue to which the vehicle will be added.
 * @param[in]     id            The ID of the vehicle to be added.
 * @param[in]     parking_time  The parking time of the vehicle to be added.
 * @param[in]     current_time  The current time when the vehicle is added to the queue.
 * @return                      returns 0 if the vehicle was successfully added to the queue, or -1 
 */
int enqueue(struct queue *queue, int id, int parking_time, int current_time);

/**
 * @brief Removes the first node(vehicle) from the queue.
 *
 * Removes the first node(vehicle) from the specified queue and frees the memory allocated for it.
 *
 * @param[out]  queue  A pointer to the queue from which the vehicle will be removed.
 * 
 * @return             returns a pointer to the removed vehicle, or NULL if the queue was empty or if the queue pointer was NULL.
 */
struct vehicle *dequeue(struct queue *queue);

/**
 * @brief Prints the queue for debugging purposes.
 *
 * Prints the vehicle_id and postion in the queue.
 * 
 * @param[in]  queue  A pointer to the queue to be printed.
 * 
 * @return            returns 0 if successful, -1 if the specified queue was empty
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
 * @return             returns 0 if successful, -1 if the queue was already NULL
 */
int free_queue(struct queue **queue);

// get_length() is not nessesary because it can be acessed directly: queue->size in O(1)
#endif 
