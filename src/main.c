#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include <stdio.h>
#include <stdlib.h>

/*
FUNKTION int main(int argc, char *argv[]){
    //inputs
    sim_parameters *inputs = get_inputs()
    
    WHILE inputs is NULL DO //retrys getting the input Parameters until there is a valid input
        PRINT "Retry entering the simulation parameters. \n" 
        inputs = get_inputs()
    END WHILE

    // seed the random number generator with the provided seed
    srand(inputs->rand_seed)

    // initialize queue, parkhaus and statistics struct
    queue *parking_queue = init_queue()
    vehicle *parkhaus = init_parkhaus(inputs->max_parking_spaces)
    stats *statistics;

    fill the statistics struct with the initial values 
        (current_time = 0, parked_cars = 0, cars_in = 0, cars_out = 0, length_queue = 0, car_in_queue = 0, last_wait_time = 0)


    // create file for running time statistics
    createRunnningTimeStatsFile(statistics) //opens a new files and saves the pointer in the struct

    // main simulation loop

    FOR current_time FROM 0 TO inputs->time_steps - 1 DO

        num_removed_cars = remove_finished_Cars(parkhaus, current_time)
        IF num_removed_cars is -1 THEN
            PRINT "Error removing finished cars from the parkhaus. \n"
        END IF

        generate a random number between 0 and 1 
        set added_vehicle_to_queue to 0 // only 0 or 1, because only one car can arrive in one time step
        IF the random number is smaller OR equal to the arrival probability THEN
            enqueue(parking_queue, current_time, (random parking time between 1 and max_parking_time), current_time)
            set added_vehicle_to_queue to 1
        END IF

        unsigned char parked_car = 0 // only 0 or 1, because only one car can park in one time step
        IF the parking queue is not empty THEN
            vehicle_to_park = dequeue(parking_queue)
            IF vehicle_to_park is not NULL THEN
                park_Car(parkhaus, vehicle_to_park, current_time)
            END IF
            parked_car = 1
        END IF

        updateStats(statistics, vehivehicle_to_park, added_vehicle_to_queue, num_removed_cars, parking_queue->size, calculate waittime form the vehicle_to_park, current_time, unsigned int car_in_queue);
        // first update the statistics before stariting to print or write to the file.
        writeRunningTimeStatsToFile(statistics)
        printRuntimeStats(statistics) // 

    printFinalStats(statistics) //print and wirte final statistics
    writeFinalStatsToFile(statistics)

    closeRunnningTimeStatsFile(statistics) //close the statistics file
    
    RETURN 0
}
*/