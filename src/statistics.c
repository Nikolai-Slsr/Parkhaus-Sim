#include <stdio.h>
#include <queue.h>
#include <parkhaus.h>


// initstats (arrat für die ganzen Variablen die gemittelt werden soll) Große: Anzahl der Simulationsschrtte

FUNCTION updateStats (pstats : pointer to stats, parked_cars, cars_in, cars_out, length_queue, last_wait_time){
    IF last_wait_time > pstats -> max_wait_time{
        pstats -> max_wait_time = last_wait_time
    }
    IF length_queue > pstats -> max_length_queue {
        pstats -> max_length_queue = length_queue
    }
    pstats -> all_cars_in += cars_in
    pstats -> all_cars_out += cars_out
    
    pstats -> sum_parkhaus_auslastung += parked_cars
    pstats -> sum_length_queue += length_queue
    pstats -> sum_wait_time += last_wait_time
}

FUNCTION printRuntimeStats (current_time, parked_cars, cars_in, cars_out, length_queue, car_in_queue, last_wait_time){
    PRINT:
            "Zeit seit Sim. Beginn:"    current_time
            "Parkhausauslastung:"       parked_cars "von" ANZAHL_STELLPLAETZE "Plaetze belegt"
            "Autos rein/raus:"          cars_in "/" cars_out
            "Laenge Warteschlange:"     length_queue "Autos + " car_in_queue "neue Autos"
            "Letzte Wartezeit:"         last_wait_time
}

FUNCTION printFinalStats (stats){
    PRINT:
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            stats.sum_parkhaus_auslastung/SIMULATION_TIME * 100
            "Länge Warteschlange Ø:"            stats.sum_length_queue/SIMULATION_TIME * 100
            "Max. Länge Warteschlange:"         stats.max_length_queue
            "Wartezeit Ø:"                      stats.sum_wait_time/SIMULATION_TIME * 100
            "ges. Anzahl Fahrzeuge rein/raus:"  stats.all_cars_in " / " stats.all_cars_out
}

FUNCTION writeStatsToFile (stats){
    CREATE new file "statistics.txt" with random number
    WRITE final stats to file:
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            stats.sum_parkhaus_auslastung/SIMULATION_TIME * 100
            "Länge Warteschlange Ø:"            stats.sum_length_queue/SIMULATION_TIME * 100
            "Max. Länge Warteschlange:"         stats.max_length_queue
            "Wartezeit Ø:"                      stats.sum_wait_time/SIMULATION_TIME * 100
            "ges. Anzahl Fahrzeuge rein/raus:"  stats.all_cars_in " / " stats.all_cars_out
    CLOSE file
}