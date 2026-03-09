#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include <stdlib.h>


vehicle **init(int Anzahl_Parkplätze){
    vehicle **pParkhaus = calloc(Anzahl_Parkplätze+1, sizeof(struct vehicle*)); //    CREATE *pArray TYPE *struct vehicle SIZE Anzahl_Parkplätze + 1 
    if(pParkhaus == NULL){
        return NULL;
    }
    vehicle *End_Point = malloc(sizeof(vehicle));
    if(End_Point == NULL){
        free(pParkhaus);
        return NULL;
    }
    End_Point->vehicle_id = -1; // CREATE struct vehicle with vehicle_id of -1 and name "End_Point"
    pParkhaus[Anzahl_Parkplätze] = End_Point;//save "End_Point" at the last Index of pParkhaus 
    return pParkhaus;

}

int isFull(vehicle *pParkhaus[]){
    if(pParkhaus == NULL){
        return -1;
    }
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){//checks if the variable saved at Index[i] is not the End_Point or is NULL 
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
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){
        if(pParkhaus[i] != NULL){
            if(pParkhaus[i]->random_park_duration <= current_time - (pParkhaus[i]->time_of_entry)){
                free(pParkhaus[i]);
                pParkhaus[i] = NULL;
                num_removed_Cars++;
                //Sollten die Cars mit Malloc initialisiert werden müssen diese hier wieder free() werden
            }   
        }   
        i++;
    }
    return num_removed_Cars;

}

int park_Car(vehicle *pParkhaus[], vehicle *pCar, int current_time){
    if(pParkhaus == NULL){
        return -1;
    }
    int i = 0;
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){
        if(pParkhaus[i] == NULL){
            pParkhaus[i] = pCar;
            pCar->time_of_entry = current_time;
            int waitTime = current_time - pCar->time_of_arrival;
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
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){
        if(pParkhaus[i] != NULL){
            used_spaces++;
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
    while(pParkhaus[i] == NULL || pParkhaus[i]->vehicle_id != -1){
        i++;
    }
    if(pParkhaus[i]->vehicle_id == -1){
        free(pParkhaus[i]);
        pParkhaus[i] = NULL;
    }
    free(pParkhaus);
    pParkhaus = NULL;
    return pParkhaus;
}
