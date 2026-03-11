#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include <stdlib.h>


vehicle **init_parkhaus(int Anzahl_Parkplätze){
    vehicle **pParkhaus = calloc(Anzahl_Parkplätze+1, sizeof(struct vehicle*)); //    CREATE *pArray TYPE *struct vehicle SIZE Anzahl_Parkplätze + 1 
    if(pParkhaus == NULL){
        return NULL;
    }
    vehicle *End_Point = malloc(sizeof(vehicle)); //The 'End_Point' has a unique ID and is always saved at the Last Spot of the Array. It is used to loop through the Array, without needing information about its length beforehand. 
    if(End_Point == NULL){
        free(pParkhaus);
        return NULL;
    }
    End_Point->vehicle_id = -1; // CREATE struct vehicle with vehicle_id of -1 and name "End_Point"
    pParkhaus[Anzahl_Parkplätze] = End_Point;//save "End_Point" at the last Index of pParkhaus 
    return pParkhaus;

}

int parkhaus_is_Full(vehicle *pParkhaus[]){
    if(pParkhaus == NULL){ //checks if the given array is initialised
        return -1;
    }
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){//this while Loop itterates through the whole Array and stops as soon as the End_point (ID = -1) is reached. We first have to check for NULL independently, because otherwise the Program would try to dereference a NULL Pointer which would crash the programm.
        if(pParkhaus[i] == NULL){ //check if no Car is present 
            return -1;       //if one is NULL then it is not full
        }   
        i++;
    }
    return 0;  //if no NULL was found then it is full
}

int remove_finished_Cars(vehicle *pParkhaus[], int current_time){
    if(pParkhaus == NULL){ 
        return -1;
    }
    int num_removed_Cars = 0;
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){ //full explanation in 'parkhaus_is_Full' Function
        if(pParkhaus[i] != NULL){
            if(pParkhaus[i]->random_park_duration <= current_time - (pParkhaus[i]->time_of_entry)){ //if the park duration is smaller than the time parked the car gets removed
                free(pParkhaus[i]); //frees the memory of the removed Car and replaces its Spot with NULL
                pParkhaus[i] = NULL;
                num_removed_Cars++;
            }   
        }   
        i++;
    }
    return num_removed_Cars;

}

int park_Car(vehicle *pParkhaus[], vehicle *pCar, int current_time){
    if(pParkhaus == NULL || pCar == NULL){ //checks if the array and Car are valid objects
        return -1;
    }
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){ //full explanation in 'Parkhaus_is_Full' Function
        if(pParkhaus[i] == NULL){ //checks for the first empty Spot in the Array
            pParkhaus[i] = pCar;
            pCar->time_of_entry = current_time; //saves the Time the Car was parked
            int waitTime = current_time - pCar->time_of_arrival; //calculates the waitTime of the Car in the queue
            return waitTime;
        }
        i++;
    }
    return -1; //if no free slot was found then return -1 to indicate failure
}

int get_Used_Spots(vehicle *pParkhaus[]){
    if(pParkhaus == NULL){
        return -1;
    }
    int used_spaces = 0;
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){ //full explanation in 'Parkhaus_is_Full' Function
        if(pParkhaus[i] != NULL){
            used_spaces++; //for every Spot which isnt empty the counter increases by one
        }
        i++;
    }
    return used_spaces;
}

vehicle** free_Parkhaus(vehicle **pParkhaus){ //only frees the array and the end pointer, not the cars. Might change that
    if(pParkhaus == NULL){
        return NULL;
    }
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){ //full explanation in 'Parkhaus_is_Full' Function
        if(pParkhaus[i] != NULL){
            free(pParkhaus[i]);     //frees the memory of every Car that is still parked
            pParkhaus[i] = NULL;
        }
        i++;
    }
    free(pParkhaus[i]);   //frees the memory of the End_Pointer because the loop stops at the last Car
    pParkhaus[i] = NULL;
    
    free(pParkhaus);        //frees the Parkhaus Array
    pParkhaus = NULL;
    return pParkhaus;       //returns the Pointer to NULL 
}
