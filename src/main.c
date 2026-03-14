/*
 * File: main.c
 * Description: Runs the parking garage simulation.
 * Initializes inputs, runs simulation loop, and prints results.
 */

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
    
    // Note: Due to changes diverging from the pseudocode in sim_parameters.c, get_inputs() handles the repeated input, and we don't have to do that in main.

    // seed the random number generator with the provided seed
    srand(p_inputs->rand_seed);

    queue *p_parking_queue = init_queue();
    if (p_parking_queue == NULL)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error initializing the parking queue. \n" ANSI_COLOR_RESET);
        free(p_inputs);
        return 1;
    }

    vehicle **p_parkhaus = init_parkhaus(p_inputs->max_parking_spaces);
    if (p_parkhaus == NULL)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error initializing the parking garage. \n" ANSI_COLOR_RESET);
        free_queue(&p_parking_queue);
        free(p_inputs);
        return 1;
    }

    stats statistics = {0}; // initialize the statistics struct with 0 values, this will be updated during the simulation

    //create file for stats
    createRunningTimeStatsFile(&statistics);
    if(statistics.p_running_stats_file == NULL)
    {
        fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error creating RunningTimeStats File. \n" ANSI_COLOR_RESET);
        p_parkhaus = free_Parkhaus(p_parkhaus);
        free_queue(&p_parking_queue);
        free(p_inputs);
        return 1;
    }

    int car_id_counter = 1;

    //main sim loop

    for (int current_time = 0; current_time < p_inputs->time_steps; current_time++)
    {
        //remove finished
        int num_removed_cars = remove_finished_Cars(p_parkhaus,current_time);
        if (num_removed_cars == -1)
        {
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error removing finished Cars. \n" ANSI_COLOR_RESET);
            closeRunningTimeStatsFile(&statistics);
            p_parkhaus = free_Parkhaus(p_parkhaus);
            free_queue(&p_parking_queue);
            free(p_inputs);
            return -1;
        }
        
        unsigned char random_arrival = rand() % 100 + 1;

        signed int added_vehicle_to_queue = 0;                       // This value stores whether a car arrived or not. It can either be 0 or 1 because only one car can arrive at the Parkhaus per time step.

        if (random_arrival <= p_inputs->arrival_probability)
        {
            int random_park_time = rand() % p_inputs->max_parking_time + 1; // Generate a random number between 0 and max_parking_time.
            enqueue(p_parking_queue, car_id_counter, random_park_time, current_time);
            car_id_counter++;
            added_vehicle_to_queue++;
        }

        int wait_time = -1;                                                 // initialize wait_time for the statistics update, it will be updated if a car is parked in this time step
        unsigned char parked_car = 0;                                       // This value stores whether a car parked or not. It can either be 0 or 1 because only one car can park at the Parkhaus per time step.
        if (p_parking_queue->size > 0 && parkhaus_is_Full(p_parkhaus) == -1)    // if there are cars in the queue and the parkhaus is not full, we can park a car
        {
            vehicle *p_vehicle_to_park = dequeue(p_parking_queue);
            added_vehicle_to_queue--;                                         // if one Car entered the queue but another one left the net. change is 0
            if (p_vehicle_to_park != NULL)
            {
                wait_time = park_Car(p_parkhaus, p_vehicle_to_park, current_time);
                if(wait_time == -1)
                {
                    fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error parking the Car. \n" ANSI_COLOR_RESET);
                    closeRunningTimeStatsFile(&statistics);
                    p_parkhaus = free_Parkhaus(p_parkhaus);
                    free_queue(&p_parking_queue);
                    free(p_inputs);
                    return 1;
                }
                parked_car = 1;
            }
            else //if the p_vehicle_to_park is NULL the dequeue operation failed
            {
                fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error dequeueing the Car. \n" ANSI_COLOR_RESET);
                closeRunningTimeStatsFile(&statistics);
                p_parkhaus = free_Parkhaus(p_parkhaus);
                free_queue(&p_parking_queue);
                free(p_inputs);
                return 1;
            }
        }
        int used_spaces = parkhaus_get_used_Spots(p_parkhaus);
        if(used_spaces == -1)
        {
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error getting the number of used parking spaces. \n" ANSI_COLOR_RESET);
            closeRunningTimeStatsFile(&statistics);
            p_parkhaus = free_Parkhaus(p_parkhaus);
            free_queue(&p_parking_queue);
            free(p_inputs);
            return 1;
        }
        updateStats(&statistics, used_spaces, parked_car, num_removed_cars, p_parking_queue->size, wait_time, current_time, added_vehicle_to_queue);  //update the Stats struct and print the runtime terminal output
        writeRunningTimeStatsToFile(&statistics);
        printRuntimeStats(&statistics, p_inputs);
    }
    printFinalStats(&statistics, p_inputs);     //print all the final statistics
    writeFinalStatsToFile(&statistics, p_inputs);
    closeRunningTimeStatsFile(&statistics);
    p_parkhaus = free_Parkhaus(p_parkhaus);     //free_parkhaus returns NULL so we assign it to p_parkhaus to avoid a dangling pointer
    free_queue(&p_parking_queue);
    free(p_inputs);
    return 0;
}