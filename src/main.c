#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include "../include/sim_parameters.h"
#include "../include/format_def.h"
#include <stdio.h>
#include <stdlib.h>


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
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error initializing the parking queue. \n" ANSI_COLOR_RESET);
        free(p_inputs);
        return 1;
    }

    vehicle **parkhaus = init_parkhaus(p_inputs->max_parking_spaces);
    if (parkhaus == NULL)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error initializing the parking garage. \n" ANSI_COLOR_RESET);
        free_queue(&parking_queue);
        free(p_inputs);
        return 1;
    }

    stats statistics = {0}; // initialize the statistics struct with 0 values, this will be updated during the simulation

    //create file for stats
    createRunningTimeStatsFile(&statistics);
    if(statistics.running_stats_file == NULL)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error creating RunningTimeStats File. \n" ANSI_COLOR_RESET);
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
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error removing finished Cars. \n" ANSI_COLOR_RESET);
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
                    fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error parking the Car. \n" ANSI_COLOR_RESET);
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
                fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error dequeueing the Car. \n" ANSI_COLOR_RESET);
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
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error getting the number of used parking spaces. \n" ANSI_COLOR_RESET);
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