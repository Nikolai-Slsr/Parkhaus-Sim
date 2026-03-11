#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include "../include/sim_parameters.h"
#include <stdio.h>
#include <stdlib.h>

/*
FUNCTION int main(int argc, char *argv[]){
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

    stats statistics = {0}; // initialize the statistics struct with 0 values, this will be updated during the simulation

    // create file for running time statistics
    createRunnningTimeStatsFile(statistics) //opens a new files and saves the pointer in the struct

    // main simulation loop

    int car_id_counter = 0 // this counter will be used to assign unique IDs to the cars

    FOR current_time FROM 0 TO inputs->time_steps - 1 DO

        num_removed_cars = remove_finished_Cars(parkhaus, current_time)
        IF num_removed_cars is -1 THEN
            PRINT "Error removing finished cars from the parkhaus. \n"
        END IF

        generate random_number between 0 and 100 //use % to cap the output to 100
        set added_vehicle_to_queue to 0 // only 0 or 1, because only one car can arrive in one time step
        IF random_number <= inputs->arrival_probability THEN
            generate random_park_time between 1 and inputs->max_parking_time // use % to cap the output to max_parking_time and then add 1 to get a number between 1 and max_parking_time
            enqueue(parking_queue, car_id_counter, random_park_time, current_time)
            incement car_id_counter by 1 
            set added_vehicle_to_queue to 1
        END IF
        wait_time = -1 // initialize wait_time for the statistics update, it will be updated if a car is parked in this time step
        unsigned char parked_car = 0 // only 0 or 1, because only one car can park in one time step
        IF the parking queue is not empty THEN
            vehicle_to_park = dequeue(parking_queue)
            IF vehicle_to_park is not NULL THEN // check if the dequeue operation was successful 
                park_Car(parkhaus, vehicle_to_park, current_time)
            END IF
            wait_time = vehicle_to_park.time_of_entry - vehicle_to_park.time_of_arrival // calculate the waiting time of the parked car, if there is a parked car
            parked_car = 1
        END IF
        
        updateStats(statistics, vehicle_to_park, added_vehicle_to_queue, num_removed_cars, parking_queue->size, wait_time, current_time, unsigned int car_in_queue);
        // first update the statistics before starting to print or write to the file.
        writeRunningTimeStatsToFile(statistics)
        printRuntimeStats(statistics)
    END FOR

    printFinalStats(statistics) //print and write final statistics
    writeFinalStatsToFile(statistics)

    closeRunnningTimeStatsFile(statistics) //close the statistics file

    RETURN 0
}
*/

int main()
{
    printf("\n|========Starting the Parkhaus Simulation for Rauenegg========| \n \n");
    sim_parameters *p_inputs = get_inputs();
    
    if (p_inputs == NULL)
    {
        return 0; // Exit cleanly if user cancelled input or allocation failed
    }
    
    // Note: due to changes diverging from the pseudo code in sim_parameters.c get_inputs() handles the repeted input and we dont have to do that in main

    // seed the random number generator with the provided seed
    srand(p_inputs->rand_seed);

    queue *parking_queue = init_queue();
    if (parking_queue == NULL)
    {
        printf("Error initializing the parking queue. \n");
        free(p_inputs);
        return 1;
    }

    vehicle **parkhaus = init_parkhaus(p_inputs->max_parking_spaces);
    if (parkhaus == NULL)
    {
        printf("Error initializing the parking garage. \n");
        free_queue(&parking_queue);
        free(p_inputs);
        return 1;
    }

    stats statistics = {0}; // initialize the statistics struct with 0 values, this will be updated during the simulation

    //create file for stats
    createRunningTimeStatsFile(&statistics);
    if(statistics.running_stats_file == NULL)
    {
        printf("Error creating RunningTimeStats File! \n");
        free_Parkhaus(parkhaus);
        free_queue(&parking_queue);
        free(p_inputs);
        return 1;
    }

    int car_id_counter = 1;

    //main sim loop

    for (int current_time = 0; current_time < p_inputs->time_steps; current_time++)
    {
        //remove finished
        int num_removed_cars = remove_finished_Cars(parkhaus,current_time);
        if (num_removed_cars == -1)
        {
            printf("Error removing finished Cars \n");
            closeRunningTimeStatsFile(&statistics);
            free_Parkhaus(parkhaus);
            free_queue(&parking_queue);
            free(p_inputs);
            return -1;
        }
        
        unsigned char random_arrival = rand() % 100;

        unsigned char added_vehicle_to_queue = 0;                       // This value stores whether a car arrived or not. It can either be 0 or 1 because only one car can arrive at the Parkhaus per time step.

        if (random_arrival <= p_inputs->arrival_probability)
        {
            int random_park_time = rand() % p_inputs->max_parking_time; // Generate a random number between 0 and max_parking_time.
            enqueue(parking_queue, car_id_counter, random_park_time, current_time);
            car_id_counter++;
            added_vehicle_to_queue = 1;
        }

        int wait_time = -1;                                                 // initialize wait_time for the statistics update, it will be updated if a car is parked in this time step
        unsigned char parked_car = 0;                                       // This value stores whether a car parked or not. It can either be 0 or 1 because only one car can park at the Parkhaus per time step.
        if (parking_queue->size > 0 && parkhaus_is_Full(parkhaus) == -1)    // if there are cars in the queue and the parkhaus is not full, we can park a car
        {
            vehicle *vehicle_to_park = dequeue(parking_queue);
            if (vehicle_to_park != NULL)
            {
                wait_time = park_Car(parkhaus, vehicle_to_park, current_time);
                if(wait_time == -1)
                {
                    printf("Error parking the car. \n");
                    closeRunningTimeStatsFile(&statistics);
                    free_Parkhaus(parkhaus);
                    free_queue(&parking_queue);
                    free(p_inputs);
                    return 1;
                }
                parked_car = 1;
            }
            else //if the vehicle_to_park is NULL the dequeue operation failed
            {
                printf("Error dequeueing the car. \n");
                closeRunningTimeStatsFile(&statistics);
                free_Parkhaus(parkhaus);
                free_queue(&parking_queue);
                free(p_inputs);
                return 1;
            }
        }
        int used_spaces = parkhaus_get_used_Spots(parkhaus);
        if(used_spaces == -1)
        {
            printf("Error getting the number of used parking spaces. \n");
            closeRunningTimeStatsFile(&statistics);
            free_Parkhaus(parkhaus);
            free_queue(&parking_queue);
            free(p_inputs);
            return 1;
        }
        updateStats(&statistics, used_spaces, parked_car, num_removed_cars, parking_queue->size, wait_time, current_time, added_vehicle_to_queue);
        writeRunningTimeStatsToFile(&statistics);
        printRuntimeStats(&statistics, p_inputs);
    }
    printFinalStats(&statistics, p_inputs);
    writeFinalStatsToFile(&statistics, p_inputs);
    closeRunningTimeStatsFile(&statistics);
    parkhaus = free_Parkhaus(parkhaus);
    free_queue(&parking_queue);
    free(p_inputs);
    return 0;
}