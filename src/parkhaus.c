/*
INCLUDE "vehicle.h"
INCLUDE "parkhaus.h"

struct vehicle *init(int Anzahl_Parkplätze)
    CREATE *Array TYPE struct vehicle SIZE Anzahl_Parkplätze + 1 
    Fill Array with NULL              //either using calloc or with a for loop
    CREATE struct vehicle with vehicle_id of -1 and name "End_Point"
    save "End_Point" at the last Index of Parkhaus
    return *Parkhaus;

END FUNCTION

int isFull(struct vehicle Parkhaus[])
    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN //checks if the variable saved at Index[i] is not the End_Point or is NULL 
        IF (Parkhaus[i] == NULL) THEN //check if no Car is present 
            return false;        //if one is NULL then it is not full
        END IF
        i = i + 1
    END WHILE

    return true;  //if no NULL was found then it is full
END FUNCTION

int remove_finished_Cars(struct vehicle *Parkhaus[], current_time)
    num_removed_Cars = 0
    i = 0
    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] != NULL)
            IF(random_park_duration OF Car AT Parkhaus[i] >= current_time - time_of_entry OF Car AT Parkhaus[i]) THEN
                Parkhaus[i] = NULL 
                num_removed_Cars = num_removed_Cars + 1
            END IF
        END IF
        i = i + 1
    END WHILE
    return num_removed_Cars

END FUNCTION

int park_Car(struct vehicle *Parkhaus[], struct Vehicle Car)

    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] == NULL) THEN
            Parkhaus[i] = Car;
            waitTime = current_time - Time_of_arrival OF Car;
            return waitTime
        END IF
    END WHILE

    return ERROR_KEIN_PLATZ_FREI

END FUNCTION

int get_Used_Spots(struct vehicle Parkhaus[])

    used_spaces = 0

    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] != NULL) THEN
            used_spaces = used_spaces + 1
        END IF
    END WHILE

    return used_spaces

END FUNCTION
*/