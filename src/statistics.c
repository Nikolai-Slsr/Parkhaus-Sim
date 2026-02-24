#include <stdio.h>
#include <queue.h>
#include <parkhaus.h>


// initstats (arrat für die ganzen Variablen die gemittelt werden soll) Große: Anzahl der Simulationsschrtte

FUNCTION updateStats (current_time, parked_cars, cars_in, cars_out, length_queue, last_waiting_time){
    stats.parkhaus_auslastung[current_time] = parked_cars
    stats.cars_in[current_time] = cars_in
    stats.cars_out[current_time] = cars_out
    stats.length_queue [current_time] = length_queue
    stats.last_wait_time [current_time] = last_wait_time

    IF last_wait_time > stats.max_wait_time{
        stats.max_wait_time = last_wait_time
    }
    IF length_queue > stats.max_length_queue {
        stats.max_length_queue = length_queue
    }
    stats.all_cars_in += cars_in_step
    stats.all_cars_out += cars_out_step
    
}

FUNCTION printRuntimeStats (current_time, parked_cars, cars_in, cars_out, length_queue, last_waiting_time){
    PRINT {
            "Zeit seit Sim. Beginn:"    current_time
            "Parkhausauslastung:"       parked_cars "von" ANZAHL_STELLPLAETZE "Plaetze belegt"
            "Autos rein/raus:"          cars_in "/" cars_out
            "Laenge Warteschlange:"     length_queue "Autos + " cars_in "neue Autos"
            "Letzte Wartezeit:"         last_waiting_time
    }

}


FUNCTION printFinalStats ()
    PRINT {
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            
            "Länge Warteschlange Ø:"           
            "Max. Länge Warteschlange:"         
            "Wartezeit Ø:"                      
            "ges. Anzahl Fahrzeuge rein/raus:"  
    }


FUNCTION writeStatsToFile