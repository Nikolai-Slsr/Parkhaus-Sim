#ifndef PARKHAUS_H
#define PARKHAUS_H

#include "vehicle.h"
/**
 * @brief Initialize a parking garage with the given size
 *
 * The function creates and returns a NULL-initialized array of type *struct Vehicle
 * with the length of the given number of parking spaces.
 * 
 * @param[in] int Anzahl_Parkplätze is used as the length of the array
 * 
 * @return *Parkhaus(struct vehicle array) Pointer to the created array
*/
vehicle** init_parkhaus(const int number_of_parking_spaces);

/** 
 * @brief Checks whether the given parking garage has free spaces
 * 
 * The function iterates through each position in the array and checks 
 * whether the slot is empty (NULL). At the first free slot, false is returned. 
 * If the loop finishes without finding a free slot, the array is completely 
 * filled with "Cars" and true is returned.
 * 
 * @param[in] struct vehicle Parkhaus[] is the array to be checked
 * 
 * @return 0/-1 Returns 0 for true (is full) or -1 for false (is not full) or for error
*/
int parkhaus_is_Full(vehicle *p_parkhaus[]);
    
/**
 * @brief Removes all cars that have exceeded their maximum parking duration
 * 
 * The function iterates through each position of the array, 
 * checks whether a "Car" is stored at that position and removes it 
 *  if it has exceeded its maximum parking duration. For this purpose, the randomly 
 * assigned value "random_park_duration" is compared with the current time minus the 
 * arrival time of the car in the parking garage. The number of removed cars is stored.
 *
 *  @param[in, out] struct vehicle *Parkhaus[] Pointer to the array to be processed 
 * 
 * @param[in] int current_time Time since Simulation begin
 * 
 * @return num_removed_Cars returns the number of cars removed during this run, -1 for error
*/
int remove_finished_Cars(vehicle *p_parkhaus[], int current_time);

/**
 * @brief Inserts a Pointer to a struct vehicle into the first free position of an array
 * 
 * The function iterates through each position of the array and stores the given 
 * "*struct vehicle Car" at the first position that contains a NULL pointer. Afterwards, 
 * the waiting time is calculated using Time_of_Arrival and the current time and returned.
 * 
 * @param[in, out] struct vehicle *Parkhaus[] Pointer to the array to be processed 
 * 
 * @param[in] struct vehicle Car car to be parked
 * 
 * @param[in] int current_time Time since Simulation begin

 * 
 * @return waitTime or -1 for error or if full
*/
int park_Car(vehicle *p_parkhaus[], vehicle *p_car, int current_time);

/**
 * @brief Counts all occupied spaces in a parking garage array
 * 
 * The function iterates through each position of the array, counts the occupied spaces 
 * and returns the total number.
 * 
 * @param[in] struct vehicle Parkhaus[] Parking garage array to be analyzed
 * 
 * @return used_spaces Number of occupied spaces, -1 for error
*/
int parkhaus_get_used_Spots(vehicle *p_parkhaus[]);

/**
 * @brief Frees the memory for the Parkhaus array
 * 
 * This function frees the memory for the End_Point struct and for the whole Parkhaus Array 
 * 
 * @param[in] struct vehicle Parkhaus[] Parking garage array to be freed
 * 
 * @return the Parkhaus Array set to NULL, or NULL for error
*/
vehicle** free_Parkhaus(vehicle **p_parkhaus);

#endif