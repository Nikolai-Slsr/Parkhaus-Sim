#ifndef PARKHAUS_H
#define PARKHAUS_H

#include "vehicle.h"
/**
@brief Initialize a parking garage with the given size

The function creates and returns a NULL-initialized array of type struct Vehicle 
with the length of the given number of parking spaces.

@param[in] int Anzahl_Parkplätze is used as the length of the array

@return *Parkhaus(struct vehicle array) Pointer to the created array
*/
struct vehicle* init(int Anzahl_Parkplätze);

/**------------------------------------------------------------------------------------------------
 
@brief Checks whether the given parking garage has free spaces

The function iterates through each position in the array and checks 
whether the slot is empty (NULL). At the first free slot, false is returned. 
If the loop finishes without finding a free slot, the array is completely 
filled with "Cars" and true is returned.

@param[in] struct vehicle Parkhaus[] is the array to be checked

@return 0/-1 Returns 0 for true (is full) or -1 for false (is not full)
*/
int is_Full(struct vehicle Parkhaus[]);
    
/**------------------------------------------------------------------------------------------------
 
@brief Removes all cars that have exceeded their maximum parking duration

The function iterates through each position of the array, 
checks whether a "Car" is stored at that position and removes it 
if it has exceeded its maximum parking duration. For this purpose, the randomly 
assigned value "random_park_duration" is compared with the current time minus the 
arrival time of the car in the parking garage. The number of removed cars is stored.

@param[in] struct vehicle *Parkhaus[] Pointer to the array to be processed 

@return num_removed_Cars returns the number of cars removed during this run
*/
int remove_finished_Cars(struct vehicle *Parkhaus[]);

/**------------------------------------------------------------------------------------------------
 
@brief Inserts a "Car" into the first free position of an array

The function iterates through each position of the array and stores the given 
"struct vehicle Car" at the first position that contains a NULL pointer. Afterwards, 
the waiting time is calculated using Time_of_Arrival and the current time and returned.

@param[in] struct vehicle *Parkhaus[] Pointer to the array to be processed 

@param[in] struct vehicle Car car to be parked

@return waitTime or Error(-1) if full
*/
int park_Car(struct vehicle *Parkhaus[], struct vehicle Car);

/**------------------------------------------------------------------------------------------------
 
@brief Counts all occupied spaces in a parking garage array

The function iterates through each position of the array, counts the occupied spaces 
and returns the total number.

@param[in] struct vehicle Parkhaus[] Parking garage array to be analyzed

@return used_spaces Number of occupied spaces
*/
int get_Used_Spots(struct vehicle Parkhaus[]);

#endif
