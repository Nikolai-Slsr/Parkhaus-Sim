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
#include <math.h>

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

void updateStats_test(){
    stats test_stats = {0};

    //first update
    updateStats (&test_stats, 4, 0, 3, 18, 0, 25, 46);

    assert(test_stats.max_wait_time == 0);
    assert(test_stats.max_length_queue == 18);
    assert(test_stats.sum_cars_in == 0);
    assert(test_stats.sum_cars_out == 3);
    assert(test_stats.sum_parkhaus_auslastung == 4);
    assert(test_stats.sum_wait_time == 0);
    assert(test_stats.sum_length_queue == 18);

    //small test for final stats
    double avg_wait_time;
    if (test_stats.sum_cars_in > 0) {
        avg_wait_time = (double)test_stats.sum_wait_time / test_stats.sum_cars_in;
    } else {
        avg_wait_time = 0.0;
    }
    assert(avg_wait_time == 0.0);   //because sum_cars_in is 0

    //second update
    updateStats(&test_stats, 14, 55, 2, 5, 4, 33, 0);

    assert(test_stats.max_wait_time == 4);
    assert(test_stats.max_length_queue == 18);
    assert(test_stats.sum_cars_in == 58);
    assert(test_stats.sum_cars_out == 5);
    assert(test_stats.sum_parkhaus_auslastung == 18);
    assert(test_stats.sum_wait_time == 4);
    assert(test_stats.sum_length_queue == 23);

    //small test for final stats
    if (test_stats.sum_cars_in > 0) {
        avg_wait_time = (double)test_stats.sum_wait_time / test_stats.sum_cars_in;
    } else {
        avg_wait_time = 0.0;
    }
    assert(fabs(avg_wait_time - 0.068965) < 1e-6); //assertion with double: difference must be over the tolerance of 1e-6
}


void sim_parameters_test(){
    //sim_parameters can really only be tested manually because it requires user input
}
int main(){
    queue_test();
    //parkhaus_test();
    //statistics_test();
    //sim_parameters_test();
}
