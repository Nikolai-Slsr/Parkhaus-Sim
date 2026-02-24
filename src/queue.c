/*
include include/queue.h
include <stdlib.h>


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

    if the queue is empty:
        set firstCar and lastCar to the new vehicle
    else:
        set lastCar's next pointer to the new vehicle
        update lastCar to the new vehicle
        increment size
        return 1 to indicate success
}
int dequeue(*queue){
        if the queue.length is 0:
        return 0 

    if queue.length is 1:
        free the memory of the only vehicle in the queue
        set firstCar and lastCar to NULL
        decrement size
        return 1
    else:
        save a pointer to the first vehicle
        update queue.firstCar to point to the second vehicle in the queue
        free the memory of the removed vehicle
        decrement size
        return 1
}

int print_queue(*queue){
    if the queue is empty:
        return 0
    else:
        initialize a pointer to the first vehicle
        while the pointer is not NULL:
            print the vehicle's id and remaining parking time
            move the pointer to the next vehicle in the queue
        return 1
}
*/