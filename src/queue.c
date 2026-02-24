/*
include include/queue.h
include stdlib.h

vehicle, node and queue structs are defined in the header file, so we can use them here without redefining them

vehicle queue init(){
    allocate memory for a new queue
    if memory allocation fails:
        return NULL to indicate failure
    set firstCar and lastCar to NULL
    set size to 0
    return the initialized queue
}

int enqueue(*queue queue, int id, int parking_time, int current_time){

    allocate memory for a new vehicle
    if memory allocation fails:
        return 0 to indicate failure
    set vehicle_id to id
    set time_of_entry to -1 to show it hasn't entered the parking lot yet
    set remaining_parktime to parking_time
    set time_of_arrival to current_time
    set random_park_duration to parking_time

    allocate memory for a node to store the vehicle
    if memory allocation fails:
        return 0 to indicate failure
    set the node's vehicle pointer to the new vehicle
    set the node's next pointer to NULL

    if the queue is empty:
        set firstCar and lastCar to the new node
        increment size
        return 1 to indicate success
    else:
        set lastCar's next pointer to the new node
        update lastCar to the new node
        increment size
        return 1 to indicate success
}
int dequeue(*queue){
        if the queue.length is 0:
        return 0 

    if queue.length is 1:
        free the memory of the vehicle in the node
        free the memory of the node -> has to be done seperately because the vehicle is in the node and won't be freed if we free the node first
        decrement size
        set firstCar and lastCar to NULL
        return 1
    else:
        save a pointer to the first node (the one to be removed)
        update queue.firstCar to point to the second node in the queue
        free the memory of the vehicle in the node
        free the memory of the node -> has to be done seperately because the vehicle is in the node and won't be freed if we free the node first
        decrement size
        return 1
}

int print_queue(*queue, int current_time){
    if the queue is empty:
        return 0
    else:
        initialize a pointer to the first node
        while the current_node is not NULL:
            print the vehicle's id and current waiting time (current_time - time_of_arrival)
            move the pointer to the next vehicle in the queue
        return 1
}

int free_queue(**queue){
    if the queue is empty:
        return 0
    else:
        initialize a pointer to the first node
        while the current_node is not NULL:
            save a pointer to the next node
            free the memory of the vehicle in the current node
            free the memory of the current node
            move to the next node using the saved pointer
        free the memory of the queue itself
        set the original queue pointer to NULL to avoid dangling pointers -> this is why we use a double pointer other wise the pinter to the original queue would still point to the now freed memory, wich could cause a segmentation fault if we try to access it after freeing the memory
        return 1
}

*/