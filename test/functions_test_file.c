/*mit diesem File können wir fürs implementieren die einzelnen Funktionen unserer Files einmal testen.
Ruft im richtigen Block einfach die Funktionen auf die ihr testen wollt und lasst euch den return 
ausprinten.*/

#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include "../include/sim_parameters.h"
#include "../include/format_def.h"

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
    printf("\n[*]Running queue_test...");

    //init_queue test
    queue *my_queue = init_queue();
    assert(my_queue != NULL);
    assert(my_queue->size == 0);
    assert(my_queue->first_node == NULL);
    assert(my_queue->last_node == NULL);
    
    //enqueue() test
    assert(enqueue(my_queue, 1, 5, 1) == 0);
    assert(enqueue(my_queue, -100, 5, -1) == -1);   //test invalid input parameters, should return -1
    my_queue = NULL;                                //reset the queue for the next test
    assert(enqueue(my_queue, 2, 3, 3) == -1);       //test for invalid queue pointer

    //dequeue() test
    assert(dequeue(my_queue) == NULL);              //test for NULL queue pointer, should return NULL
    my_queue = init_queue();
    assert(dequeue(my_queue) == NULL);              //test for empty queue, should return NULL
    enqueue(my_queue, 1, 5, 1);
    assert(dequeue(my_queue)->vehicle_id == 1);     //test for correct dequeue

    //print_queue() will not be tested here because it only prints the queue and does not return any value (Was manualy tested and works as expected)

    //test freeing the queue
    assert(free_queue(&my_queue) == 0);             //test for successful freeing
    assert(my_queue == NULL);                       //check if the original queue pointer is set to NULL
    my_queue = NULL;
    assert(free_queue(&my_queue) == -1);            //test for invalid queue pointer, should return -1
}
//--------------------------------------------------------- 
//functions for parkhaus_test; because we have to test quite a lot for some functions to ensure correct functionality, I wrote the tests for all Functions in their own Test_Function
void test_init_parkhaus(void){
    vehicle **parkhaus = init_parkhaus(10);

    assert(parkhaus[10]->vehicle_id == -1);
    assert(parkhaus[9] == NULL);
    parkhaus = free_Parkhaus(parkhaus);
}
void test_park_Car(void){
    vehicle **parkhaus;
    parkhaus = init_parkhaus(10);
    vehicle *Car1 = malloc(sizeof(vehicle));
    Car1->vehicle_id = 1;
    Car1->time_of_arrival = 1;
    vehicle *Car2 = malloc(sizeof(vehicle));
    Car2->vehicle_id = 2;
    Car2->time_of_arrival = 2;

    assert(parkhaus[0] == NULL); //Testing if the first Spot is empty
    
    assert(park_Car(parkhaus, Car1, 2) == 1); //Testing if the waitTime is correct
    assert(parkhaus[0] != NULL);
    assert(parkhaus[0]->vehicle_id == 1); //Testing if the first Spot isnt empty and if it contains the right Car
    assert(parkhaus[0]->time_of_entry == 2);

    assert(park_Car(parkhaus, Car2, 4) == 2); //Testing if the waitTime is correct
    assert(parkhaus[1] != NULL);
    assert(parkhaus[1]->vehicle_id == 2); //Testing if the second Spot isnt empty and if it contains the right Car
    assert(parkhaus[1]->time_of_entry == 4);

    assert(parkhaus[0]->vehicle_id == 1); //Testing that nothing has changed with the first Spot

    parkhaus = free_Parkhaus(parkhaus);
    assert(park_Car(parkhaus, Car1, 0) == -1); //Testing if Function recognises empty array as Error
    return;
}
void test_parkhaus_is_Full(void){
    vehicle **parkhaus = init_parkhaus(10);
    assert(parkhaus_is_Full(parkhaus) == -1);
    for(int i=0; i<10; i++){
        vehicle *Car = malloc(sizeof(vehicle));
        Car->vehicle_id = i;
        park_Car(parkhaus, Car, 1);
    }
    assert(parkhaus_is_Full(parkhaus) == 0);

    parkhaus = free_Parkhaus(parkhaus);

}
void test_parkhaus_get_used_Spots(void){
    vehicle **parkhaus;
    parkhaus = init_parkhaus(10);
    vehicle *Car1 = malloc(sizeof(vehicle));
    Car1->vehicle_id = 1;
    vehicle *Car2 = malloc(sizeof(vehicle));
    Car2->vehicle_id = 2;
    
    assert(parkhaus_get_used_Spots(parkhaus) == 0); //Testing with no Cars
    park_Car(parkhaus, Car1, 1);
    
    assert(parkhaus_get_used_Spots(parkhaus) == 1); //Testing with one Car
    park_Car(parkhaus, Car2, 2);
    
    assert(parkhaus_get_used_Spots(parkhaus) == 2); //Testing with two Cars

    parkhaus = free_Parkhaus(parkhaus);
    assert(parkhaus_get_used_Spots(parkhaus) == -1); //Testing if Function recognises empty array as Error
    return;
}
void test_remove_finished_cars(void){
    vehicle **parkhaus;
    parkhaus = init_parkhaus(10);
    vehicle *Car1 = malloc(sizeof(vehicle));
    Car1->vehicle_id = 1;
    Car1->random_park_duration = 5;
    vehicle *Car2 = malloc(sizeof(vehicle));
    Car2->random_park_duration = 5;
    Car2->vehicle_id = 2;

    park_Car(parkhaus, Car1, 1); //Parking both Cars at Time 1
    park_Car(parkhaus, Car2, 1); 

    assert(remove_finished_Cars(parkhaus, 2) == 0); //Testing if no Car was removed at Time 2
    assert(remove_finished_Cars(parkhaus, 6) == 2); //Testing if both Cars were removed at Time 6

    assert(parkhaus_get_used_Spots(parkhaus) == 0); //Testing if the Cars really were removed

    parkhaus = free_Parkhaus(parkhaus);
    assert(parkhaus_get_used_Spots(parkhaus) == -1); //Testing if Function recognises empty array as Error
    
    return;
}
void test_free_Parkhaus(void){
    vehicle **parkhaus;
    parkhaus = init_parkhaus(10);

    parkhaus = free_Parkhaus(parkhaus);
    assert(parkhaus == NULL);
    assert(free_Parkhaus(parkhaus) == NULL);
    return;
}
//---------------------------------------------------------

void parkhaus_test(){
    printf("\n[*]Running parkhaus_test...");

    test_init_parkhaus();
    test_free_Parkhaus();
    test_park_Car();
    test_parkhaus_is_Full();
    test_parkhaus_get_used_Spots();
    test_remove_finished_cars();
}

void updateStats_test()
{
    printf("\n[*]Running statistics_test...");

    stats test_stats = {0};

    //first update
    updateStats (&test_stats, 4, 0, 3, 18, 0, 25, 46);

    assert(test_stats.max_wait_time == 0);
    assert(test_stats.max_queue_length == 18);
    assert(test_stats.sum_cars_entered == 0);
    assert(test_stats.sum_cars_exited == 3);
    assert(test_stats.sum_parking_occupancy == 4);
    assert(test_stats.sum_wait_time == 0);
    assert(test_stats.sum_queue_length == 18);

    //small test for final stats
    double avg_wait_time;
    if (test_stats.sum_cars_entered > 0) {
        avg_wait_time = (double)test_stats.sum_wait_time / test_stats.sum_cars_entered;
    } else {
        avg_wait_time = 0.0;
    }
    assert(avg_wait_time == 0.0);   //because sum_cars_entered is 0

    //second update
    updateStats(&test_stats, 14, 55, 2, 5, 4, 33, 0);

    assert(test_stats.max_wait_time == 4);
    assert(test_stats.max_queue_length == 18);
    assert(test_stats.sum_cars_entered == 55);
    assert(test_stats.sum_cars_exited == 5);
    assert(test_stats.sum_parking_occupancy == 18);
    assert(test_stats.sum_wait_time == 4);
    assert(test_stats.sum_queue_length == 23);

    //small test for final stats
    if (test_stats.sum_cars_entered > 0) {
        avg_wait_time = (double)test_stats.sum_wait_time / test_stats.sum_cars_entered;
    } else {
        avg_wait_time = 0.0;
    }
    assert(fabs(avg_wait_time - 0.072727) < 1e-6); //assertion with double: difference must be over the tolerance of 1e-6
}


void sim_parameters_test(){
    //sim_parameters can really only be tested manually because it requires user input
}
int main(){
    printf("\n[*]Running Test...\n");
    queue_test();
    printf("\n[*]queue_test passed!");
    parkhaus_test();
    printf("\n[*]parkhaus_test passed!");
    updateStats_test();
    printf("\n[*]statistics_test passed!\n");
    //sim_parameters_test();
    printf(ANSI_BOLD ANSI_COLOR_GREEN "\n[*]Passed all Tests!\n\n" ANSI_COLOR_RESET);
}
