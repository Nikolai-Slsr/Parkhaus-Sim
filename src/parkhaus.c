/*
INCLUDE "vehicle.h"
INCLUDE "parkhaus.h"

FUNCTION *init(int Anzahl_Parkplätze) //Initialisieren eines Parkhaus Arrays mit Anzahl der Parkplätze welches mit NULL Pointern gefüllt ist
    CREATE *Array TYPE struct vehicle SIZE Anzahl_Parkplätze + 1 
    Fill Array with NULL              // entweder mit calloc initialisieren oder per for Schleife
    CREATE struct vehicle Car with vehicle_id of -1 and name "End_Point"
    save "End_Point" at the last Index of Parkhaus
    return *Parkhaus;

END FUNCTION

FUNCTION isFull(struct vehicle Parkhaus[]) //Checken ob das Parkhaus noch freie Plätze hat. Gibt True oder False zurück
    i = 0
    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF (Parkhaus[i] == NULL) THEN //check für jeden Platz ob kein Auto drinne ist(NULL), 
            return false;        // wenn ein Platz nicht belegt ist gebe false zurück
        END IF
        i = i + 1
    END WHILE

    return true;  //wenn alle durch sind und kein NULL gefunden wurde dann ist es voll
END FUNCTION

FUNCTION remove_finished_Cars(struct vehicle *Parkhaus[], current_time) //geht jeden Platz eines arrays Parkhaus durch und entfernt alle Autos die ihre Parkdauer überschritten haben, gibt die Anzahl der entfernten Autos zurück
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

FUNCTION park_Car(struct vehicle *Parkhaus[], struct Vehicle Car) //Speichert ein gegebenes Car im ersten freien Platz des Arrays und gibt die Zeit die das Auto in der Queue war zurück

    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] == NULL) THEN
            Parkhaus[i] = Car;
            waitTime = current_time - Time_of_arrival OF Car;
            return waitTime
        END IF
    END WHILE

    return ERROR_KEIN_PLATZ_FREI

END FUNCTION

FUNCTION get_Used_Spots(struct vehicle Parkhaus[]) //ermittelt die Anzahl der belegten Plätze eines gegebenen Parkhaus

    int used_spaces = 0;

    WHILE (Variable of Parkhaus at Index[i] is not "End_Point" or is NULL) THEN
        IF(Parkhaus[i] != NULL) THEN
            used_spaces = used_spaces + 1
        END IF
    END WHILE

    return used_spaces

END FUNCTION
*/