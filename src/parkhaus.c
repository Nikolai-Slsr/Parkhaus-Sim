include vehicle.h
include bool.h

Vehicle init(int Anzahl_Parkplätze){
    Parkhaus = Array des typ struct vehicle [Anzahl_Parkplätze]
    Fill Array with NULL
    return *Array;
}

bool isFull(array Parkhaus){
    for(ANZAHL_PARKPLÄTZE){
        IF(Parkhaus[i] == NULL){ //check für jeden Platz ob kein Auto drinne ist(NULL), 
            return false;        // wenn ein Platz nicht belegt ist gebe false zurück
        }
    }
    return true;                 //wenn alle durch sind und kein NULL gefunden wurde dann ist es voll
}

int remove_finished_Cars(array *Parkhaus){ //geht jeden Platz eines arrays Parkhaus durch und entfernt alle Autos die ihre Parkdauer überschritten haben, gibt ein int mit der Anzahl der entfernten Autos zurück
    int removed_Cars = 0;
    for(ANZAHL_PARKPLÄTZE){
        IF(Parkhaus[i]->random_park_duration >= time - Parkhaus[i]->time_of_arrival){
            Parkhaus[i] = NULL;
            removed_CARS++;
        }
    }
    return removed_Cars;

}

FUNCTION Park_Car(array *Parkhaus, Vehicle Car){
    for(ANZAHL_PARKPLÄTZE){
        IF(Parkhaus[i] == NULL){
            Parkhaus[i] = Car;
            return AUTO_EINGEPARKT;
        }
    }
    return ERROR_KEIN_PLATZ_GEFUNDEN
}

int get_Used_Spots(){
    int counter = 0;
    for(ANZAHL_PARKPLÄTZE){
        IF(Parkhaus[i] != NULL){
            counter ++;
        }
    }
    return counter;
}