/*
 * File: parkhaus.c
 * Description: Implements parking garage array management.
 * Provides functions for parked vehicle management.
 */

#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include <stdlib.h>


vehicle **init_parkhaus(int number_of_parking_spaces){
    vehicle **p_parkhaus = calloc(number_of_parking_spaces + 1, sizeof(struct vehicle*)); //    CREATE *pArray TYPE *struct vehicle SIZE Anzahl_Parkplätze + 1 
    if(p_parkhaus == NULL)
    {
        return NULL;
    }
    vehicle *p_end_point = malloc(sizeof(vehicle)); //The 'End_Point' has a unique ID and is always saved at the Last Spot of the Array. It is used to loop through the Array, without needing information about its length beforehand. 
    if(p_end_point == NULL)
    {
        free(p_parkhaus);
        return NULL;
    }
    p_end_point->vehicle_id = -1; // CREATE struct vehicle with vehicle_id of -1 and name "End_Point"
    p_parkhaus[number_of_parking_spaces] = p_end_point;//save "End_Point" at the last Index of pParkhaus 
    return p_parkhaus;

}

int parkhaus_is_Full(vehicle *p_parkhaus[])
{
    if(p_parkhaus == NULL) //checks if the given array is initialised
    { 
        return -1;
    }
    int i = 0;
    while(p_parkhaus[i] == NULL || p_parkhaus[i]->vehicle_id != -1) //this while Loop itterates through the whole Array and stops as soon as the End_point (ID = -1) is reached. We first have to check for NULL independently, because otherwise the Program would try to dereference a NULL Pointer which would crash the programm.
    {
        if(p_parkhaus[i] == NULL) //check if no Car is present 
        { 
            return -1;       //if one is NULL then it is not full
        }   
        i++;
    }
    return 0;  //if no NULL was found then it is full
}

int remove_finished_Cars(vehicle *p_parkhaus[], int current_time)
{
    if(p_parkhaus == NULL)
    { 
        return -1;
    }
    int num_removed_cars = 0;
    int i = 0;
    while(p_parkhaus[i] == NULL || p_parkhaus[i]->vehicle_id != -1) //full explanation in 'parkhaus_is_Full' Function
    { 
        if(p_parkhaus[i] != NULL)
        {
            if(p_parkhaus[i]->random_park_duration <= current_time - (p_parkhaus[i]->time_of_entry)) //if the park duration is smaller than the time parked the car gets removed
            { 
                free(p_parkhaus[i]); //frees the memory of the removed Car and replaces its Spot with NULL
                p_parkhaus[i] = NULL;
                num_removed_cars++;
            }   
        }   
        i++;
    }
    return num_removed_cars;

}

int park_Car(vehicle *p_parkhaus[], vehicle *p_car, int current_time)
{
    if(p_parkhaus == NULL || p_car == NULL) //checks if the array and Car are valid objects
    { 
        return -1;
    }
    int i = 0;
    while(p_parkhaus[i] == NULL || p_parkhaus[i]->vehicle_id != -1) //full explanation in 'Parkhaus_is_Full' Function
    { 
        if(p_parkhaus[i] == NULL) //checks for the first empty Spot in the Array
        { 
            p_parkhaus[i] = p_car;
            p_car->time_of_entry = current_time; //saves the Time the Car was parked
            int wait_time = current_time - p_car->time_of_arrival; //calculates the waitTime of the Car in the queue
            return wait_time;
        }
        i++;
    }
    return -1; //if no free slot was found then return -1 to indicate failure
}

int parkhaus_get_used_Spots(vehicle *p_parkhaus[])
{
    if(p_parkhaus == NULL)
    {
        return -1;
    }
    int used_spaces = 0;
    int i = 0;
    while(p_parkhaus[i] == NULL || p_parkhaus[i]->vehicle_id != -1) //full explanation in 'Parkhaus_is_Full' Function
    { 
        if(p_parkhaus[i] != NULL)
        {
            used_spaces++; //for every Spot which isnt empty the counter increases by one
        }
        i++;
    }
    return used_spaces;
}

vehicle** free_Parkhaus(vehicle **p_parkhaus) //only frees the array and the end pointer, not the cars. Might change that
{ 
    if(p_parkhaus == NULL)
    {
        return NULL;
    }
    int i = 0;
    while(p_parkhaus[i] == NULL || p_parkhaus[i]->vehicle_id != -1) //full explanation in 'Parkhaus_is_Full' Function
    { 
        if(p_parkhaus[i] != NULL)
        {
            free(p_parkhaus[i]);     //frees the memory of every Car that is still parked
            p_parkhaus[i] = NULL;
        }
        i++;
    }
    free(p_parkhaus[i]);   //frees the memory of the End_Pointer because the loop stops at the last Car
    p_parkhaus[i] = NULL;
    
    free(p_parkhaus);        //frees the Parkhaus Array
    p_parkhaus = NULL;
    return p_parkhaus;       //returns the Pointer to NULL 
}
