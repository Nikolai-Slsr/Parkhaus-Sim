/*
INCLUDE "vehicle.h"
INCLUDE "parkhaus.h"

FUNCTION struct vehicle *init(int Anzahl_Parkplätze)
    CREATE *pArray TYPE *struct vehicle SIZE Anzahl_Parkplätze + 1 
    Fill pArray with NULL              //either using calloc or with a for loop
    CREATE struct vehicle with vehicle_id of -1 and name "End_Point"
    save "End_Point" at the last Index of pParkhaus
    return *pParkhaus;

END FUNCTION

FUNCTION int isFull(const struct vehicle *pParkhaus[])
    WHILE (Variable of pParkhaus at Index[i] is not "End_Point" or is NULL) THEN //checks if the variable saved at Index[i] is not the End_Point or is NULL 
        IF (pParkhaus[i] == NULL) THEN //check if no Car is present 
            return -1       //if one is NULL then it is not full
        END IF
        i = i + 1
    END WHILE

    return 0  //if no NULL was found then it is full
END FUNCTION

FUNCTION int remove_finished_Cars(struct vehicle *pParkhaus[], int current_time)
    IF pParkhaus == NULL THEN
        return -1
    END IF
    num_removed_Cars = 0
    i = 0
    WHILE (Variable of pParkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(pParkhaus[i] != NULL)
            IF(random_park_duration OF Car AT pParkhaus[i] >= current_time - (time_of_entry OF Car AT pParkhaus[i])) THEN
                pParkhaus[i] = NULL 
                num_removed_Cars = num_removed_Cars + 1
            END IF
        END IF
        i = i + 1
    END WHILE
    return num_removed_Cars

END FUNCTION

FUNCTION int park_Car(struct vehicle *pParkhaus[], struct Vehicle *pCar)
    IF pParkhaus == NULL THEN
        return -1
    END IF
    WHILE (Variable of pParkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(pParkhaus[i] == NULL) THEN
            pParkhaus[i] = *pCar;
            waitTime = current_time - Time_of_arrival OF *pCar;
            return waitTime
        END IF
    END WHILE

    return -1 //if no free slot was found then return -1 to indicate failure

END FUNCTION

FUNCTION int get_Used_Spots(const struct vehicle *pParkhaus[])
    IF pParkhaus == NULL THEN
        return -1
    END IF
    used_spaces = 0

    WHILE (Variable of pParkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(pParkhaus[i] != NULL) THEN
            used_spaces = used_spaces + 1
        END IF
    END WHILE

    return used_spaces

END FUNCTION
*/
