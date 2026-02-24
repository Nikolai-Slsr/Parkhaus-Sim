#include <stdio.h>
#include <queue.h>
#include <parkhaus.h>


// initstats (arrat für die ganzen Variablen die gemittelt werden soll) Große: Anzahl der Simulationsschrtte

FUNCTION updateStats (current_time, parked_cars, cars_in, cars_out, length_queue, last_waiting_time):
    stats.parkhaus_auslastung[current_time] = parked_cars
    stats.cars_in[current_time] = cars_in
    stats.cars_out[current_time] = cars_out
    stats.length_queue [current_time] = length_queue
    stats.last_waiting_time [current_time] = last_waiting_time

    


FUNCTION printRuntimeStats ()


FUNCTION printFinalStats

FUNCTION writeStatsToFile