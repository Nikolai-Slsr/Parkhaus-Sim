/*mit diesem File können wir fürs implementieren die einzelnen Funktionen unserer Files einmal testen.
Ruft im richtigen Block einfach die Funktionen auf die ihr testen wollt und lasst euch den return 
ausprinten.*/

#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include "../include/sim_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Unit tests for the functions in queue.c
 * 
 * This function tests the following functions:
 * - init_queue
 * - enqueue
 * - dequeue
 * - free_queue
 * 
 */
void queue_test(){
    //init_queue test
    queue *my_queue = init_queue();
    assert(my_queue != NULL);
    
    //enqueue test
    assert(enqueue(my_queue, 1, 5, 1) == 0);
    assert(enqueue(my_queue, -100, 5, -1) == -1);   //test invalid input parameters, should return -1
    my_queue = NULL;                                 //reset the queue for the next test
    assert(enqueue(my_queue, 2, 3, 3) == -1);       //test for invalid queue pointer

    //dequeue test
    assert(dequeue(my_queue) == NULL);              //test for NULL queue pointer, should return NULL
    my_queue = init_queue();
    assert(dequeue(my_queue) == NULL);              //test for empty queue, should return NULL
    enqueue(my_queue, 1, 5, 1);
    assert(dequeue(my_queue)->vehicle_id == 1);     //test for correct dequeue

    //print_queue will not be tested here because it only prints the queue and does not return any value (Was manualy tested and works as expected)

    //test freeing the queue
    assert(free_queue(&my_queue) == 0);             //test for successful freeing
    assert(my_queue == NULL);                       //check if the original queue pointer is set to NULL
    my_queue = NULL;
    assert(free_queue(&my_queue) == -1);            //test for invalid queue pointer, should return -1
}

void parkhaus_test(){

}

void statistics_test(){

}

void sim_parameters_test(){

}
int main(){
    queue_test();
    //parkhaus_test();
    //statistics_test();
    //sim_parameters_test();
}
