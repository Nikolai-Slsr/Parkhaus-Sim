/*
INCLUDE "vehicle.h"
INCLUDE "parkhaus.h"

FUNCTION struct vehicle *init_parkhaus(int Anzahl_Parkplätze)
    CREATE *Array TYPE struct vehicle SIZE Anzahl_Parkplätze + 1 
    Fill Array with NULL              //either using calloc or with a for loop
    CREATE struct vehicle with vehicle_id of -1 and name "End_Point"
    save "End_Point" at the last Index of Parkhaus
    return *Parkhaus;

END FUNCTION

FUNCTION int isFull(const struct vehicle *Parkhaus[])
    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN //checks if the variable saved at Index[i] is not the End_Point or is NULL 
        IF (Parkhaus[i] == NULL) THEN //check if no Car is present 
            return -1       //if one is NULL then it is not full
        END IF
        i = i + 1
    END WHILE

    return 0  //if no NULL was found then it is full
END FUNCTION

FUNCTION int remove_finished_Cars(struct vehicle *Parkhaus[], int current_time)
    IF Parkhaus == NULL THEN
        return -1
    END IF
    num_removed_Cars = 0
    i = 0
    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] != NULL)
            IF(random_park_duration OF Car AT Parkhaus[i] >= current_time - (time_of_entry OF Car AT Parkhaus[i])) THEN
                Parkhaus[i] = NULL 
                num_removed_Cars = num_removed_Cars + 1
            END IF
        END IF
        i = i + 1
    END WHILE
    return num_removed_Cars

END FUNCTION

FUNCTION int park_Car(struct vehicle *Parkhaus[], struct Vehicle Car)
    IF Parkhaus == NULL THEN
        return -1
    END IF
    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] == NULL) THEN
            Parkhaus[i] = Car;
            waitTime = current_time - Time_of_arrival OF Car;
            return waitTime
        END IF
    END WHILE

    return -1 //if no free slot was found then return -1 to indicate failure

END FUNCTION

FUNCTION int get_Used_Spots(const struct vehicle *Parkhaus[])
    IF Parkhaus == NULL THEN
        return -1
    END IF
    used_spaces = 0

    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] != NULL) THEN
            used_spaces = used_spaces + 1
        END IF
    END WHILE

    return used_spaces

END FUNCTION
*/
