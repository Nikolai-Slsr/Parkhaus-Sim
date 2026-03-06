/*
#include "../include/queue.h"
#include <stdlib.h>
#include "../include/vehicle.h"

node and queue structs are defined in include/queue.h, so we can use them here without redefining them
vehicle struct is defined in include/vehicle.h, so we can use it here also
*/
#include "../include/queue.h"
#include <stdlib.h>
#include "../include/vehicle.h"

// FUNCTION queue *init_queue()
//     allocate memory for a new queue
//     IF memory allocation fails THEN
//         RETURN NULL to indicate failure
//     END IF
//     set firstCar and lastCar to NULL
//     set size to 0
//     RETURN the initialized queue pointer
// END FUNCTION
queue *init_queue(){
    queue *p_new_queue = calloc(1, sizeof(queue)); //use calloc to automatically initalize the queue with 0 and NULL
    if (p_new_queue == NULL)
    {
        return NULL;
    }
    return p_new_queue;
}

/*
FUNCTION int enqueue(queue *queue, int id, int parking_time, int current_time)
    if the queue pointer is NULL THEN
        RETURN -1 to indicate failure
    END IF

    allocate memory for a new vehicle
    IF memory allocation for vehicle fails THEN
        RETURN -1 to indicate failure
    END IF
    set vehicle_id to id
    set time_of_entry to -1 -> to show it hasn't entered the parking lot yet
    set remaining_parktime to parking_time
    set time_of_arrival to current_time
    set random_park_duration to parking_time

    allocate memory for a node to store the vehicle

    IF memory allocation for node fails THEN
        Free the memory allocated for the vehicle to avoid memory leaks
        RETURN -1 to indicate failure
    END IF
    set the node's vehicle pointer to the new vehicle
    set the node's next pointer to NULL

    IF the queue is empty THEN
        set first_node and last_node to the new node
        increment size
        RETURN 0 to indicate success
    ELSE
        set lastCar's next pointer to the new node
        update lastCar to the new node
        increment size
        RETURN 0 to indicate success
    END IF
END FUNCTION
*/
int enqueue(queue *p_queue, int id, int parking_time, int current_time){
    if (p_queue == NULL) //check for a valid queue
    {
        return -1;
    }

    vehicle *p_new_vehicle = calloc(1, sizeof(vehicle)); //Initialize with calloc to avoid accidentally accessing wrong data down the line.
    if (p_new_vehicle == NULL)
    {
        return -1;
    }

    // Set the vehicle's parameters
    p_new_vehicle->vehicle_id = id;
    p_new_vehicle->time_of_entry = -1; //to show it hasn't entered the parking lot yet
    p_new_vehicle->remaining_parktime = parking_time;
    p_new_vehicle->time_of_arrival = current_time;
    p_new_vehicle->random_park_duration = parking_time;

    node *p_new_node = malloc(sizeof(node));
    if (p_new_node == NULL)
    {
        free(p_new_vehicle); // Free the memory allocated for the vehicle to avoid memory leaks
        return -1;
    }
    p_new_node->vehicle = p_new_vehicle;
    p_new_node->next = NULL;

    if (p_queue->size == 0) //special case for length = 0 because first_node has to also be set to the new node.
    {
        p_queue->first_node = p_new_node;
        p_queue->last_node = p_new_node;
        p_queue->size++;
        return 0;
    }
    else
    {
        p_queue->last_node->next = p_new_node;
        p_queue->last_node = p_new_node;
        p_queue->size++;
        return 0;
    }
}
/*
FUNCTION vehicle *dequeue(queue *queue)
    IF the queue->size is 0 OR queue ist NULL THEN
        RETURN -1
    END IF

    IF queue->length is 1 THEN
        save pointer to vehicle in the first node
        free the memory of the node
        decrement size
        set firstCar and lastCar to NULL
        RETURN pointer to saved vehicle
    ELSE
        save pointer to vehicle in the first node
        save a pointer to the first node (the one to be removed)
        update queue->firstCar to point to the second node in the queue
        free the memory of the node
        decrement size
        RETURN pointer to saved vehicle
    END IF
END FUNCTION
*/

vehicle *dequeue(queue *p_queue){
    if (p_queue == NULL || p_queue->size == 0)
    {
        return NULL;
    }
    if (p_queue->size == 1)
    {
        vehicle *p_removed_vehicle = p_queue->first_node->vehicle;
        free(p_queue->first_node);
        p_queue->size--;
        p_queue->first_node = NULL;
        p_queue->last_node = NULL;
        return p_removed_vehicle;
    }
    else
    {
        vehicle *p_removed_vehicle = p_queue->first_node->vehicle;
        node *p_removed_node = p_queue->first_node;
        p_queue->first_node = p_removed_node->next;
        free(p_removed_node);
        p_queue->size--;
        return p_removed_vehicle;
    }
}
/*
FUNCTION int print_queue(queue *queue)
    IF the queue is empty or NULL THEN
        RETURN -1
    ELSE
        initialize a pointer to the first node
        WHILE: the current_node is not NULL DO
            print the vehicle's id and the positon in the queue
            move the pointer to the next vehicle in the queue
        END WHILE
        RETURN 0
    END IF
END FUNCTION
*/
int print_queue(queue *p_queue){
    if (p_queue == NULL || p_queue->size == 0)
    {
        print_queue("The queue is empty. \n");
        return -1;
    }
    else
    {
        node *p_current_node = p_queue->first_node;
        while (p_current_node != NULL)
        {
            printf("Vehicle ID: %d, Position in Queue: %d \n", p_current_node->vehicle->vehicle_id, p_queue->size);
            p_current_node = p_current_node->next;
        }
        return 0;
    }
}
/*
FUNCTION int free_queue(queue **queue)
    IF the queue pointer is NULL THEN
        RETURN -1 to indicate failure
    END IF
    IF queue->size = 0 THEN
        free the memory of the queue itself
        RETURN 0
    ELSE
        initialize a pointer to the first node
        WHILE: the current_node is not NULL DO
            save a tmp pointer to the next node
            free the memory of the vehicle in the current node
            free the memory of the current node
            move to the next node using the tmp pointer
        END WHILE
        free the memory of the queue itself
        set the original queue pointer to NULL //to avoid dangling pointers; this is why we use a double pointer other wise the pinter to the original queue would still point to the now freed memory, wich could cause a segmentation fault IF we try to access it after freeing the memory
        RETURN 0
    END IF
END FUNCTION
*/
