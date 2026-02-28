#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include "../include/sim_parameters.h"
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
    IF parking_queue is NULL THEN // check if the queue was initialized successfully
        PRINT "Error initializing the parking queue. \n"
        RETURN 1
    END IF

    vehicle *parkhaus = init_parkhaus(inputs->max_parking_spaces)
    IF parkhaus is NULL THEN // check if the parkhaus was initialized successfully
        PRINT "Error initializing the parking garage. \n"
        RETURN 1
    END IF

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

        generate random_number between 0 and 1 //use % to cap the output to 10000 and then divide by 10000.0 to get a number between 0 and 1
        set added_vehicle_to_queue to 0 // only 0 or 1, because only one car can arrive in one time step
        IF random_number <= inputs->arrival_probability THEN
            generate random_park_time between 1 and inputs->max_parking_time // use % to cap the output to max_parking_time and then add 1 to get a number between 1 and max_parking_time
            enqueue(parking_queue, current_time, random_park_time, current_time)
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