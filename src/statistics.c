#include <stdio.h>
#include "queue.h"
#include "parkhaus.h"


/**
 * FUNCTION updateStats (stats *pstats, int parked_cars, int cars_in, int cars_out, int length_queue, int last_wait_time, int current_time, int car_in_queue){
    IF last_wait_time > pstats -> max_wait_time{
        pstats -> max_wait_time = last_wait_time
    }
    IF length_queue > pstats -> max_length_queue {
        pstats -> max_length_queue = length_queue
    }
    pstats -> sum_cars_in += cars_in
    pstats -> sum_cars_out += cars_out
    
    pstats -> sum_parkhaus_auslastung += parked_cars
    pstats -> sum_length_queue += length_queue
   IF last_wait_time > 0{
    sum_wait_time += last_wait_time
   }

    pstats -> current_time = current_time
    pstats -> parked_cars = parked_cars
    pstats -> cars_in = cars_in
    pstats -> cars_out = cars_out
    pstats -> length_queue = length_queue
    pstats -> car_in_queue = car_in_queue
    pstats -> last_wait_time = last_wait_time
    }

in the following, the print functions do not follow the intended visualization idea, just the concept.

FUNCTION printRuntimeStats (const stats *pstats){
    PRINT:
            "Zeit seit Sim. Beginn:"    pstats -> current_time
            "Parkhausauslastung:"       pstats -> parked_cars "von" ANZAHL_STELLPLAETZE "Plaetze belegt"
            "Autos rein/raus:"          pstats -> cars_in "/" pstats -> cars_out
            "Laenge Warteschlange:"     pstats -> length_queue "Autos + " pstats -> car_in_queue "neue Autos"
            "Letzte Wartezeit:"         pstats -> last_wait_time
}

FUNCTION createRunnningTimeStatsFile(stats *pstats){
    char filename [50];
    int counter = 1;

    WHILE (1)
        filename = "running_stats_" + counter + ".txt"

        IF file filename DOES NOT EXIST
            BREAK
        END IF

        counter ++
    END WHILE

    OPEN filename FOR WRITING
    SAVE file pointer in pstats->running_stats_file

    IF file pointer IS NULL
        PRINT error
        EXIT program
    END IF

    PRINT "Created file:" filename
}

FUNCTION writeRunningTimeStatsToFile(const stats *pstats){
    WRITES TO FILE{
        //a table layout for every statistics parameter:
        Time stamp:             Parked cars:            new cars in:        cars out:               length queue:           cars in queue:          last wait time:

        //then writes the parameters into the table. every new timestep is a new line
        pstats -> current_time   pstats -> parked_cars   pstats -> cars_in   pstats -> cars_out   pstats -> length_queue   pstats -> car_in_queue   pstats -> last_wait_time
        NEW LINE
        //this is not the right format, just the concept
    }
}

FUNCTION closeRunnningTimeStatsFile(stats *pstats){
    IF pstats->running_stats_file IS NOT NULL
        CLOSE pstats->running_stats_file
        SET pstats->running_stats_file TO NULL
    END IF
}

FUNCTION printFinalStats (const stats *pstats){
    PRINT:
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            pstats->sum_parkhaus_auslastung/SIMULATION_TIME
            "Länge Warteschlange Ø:"            pstats->sum_length_queue/SIMULATION_TIME
            "Max. Länge Warteschlange:"         pstats->max_length_queue
            "Wartezeit Ø:"                      pstats->sum_wait_time/pstats->sum_cars_in
            "ges. Anzahl Fahrzeuge rein/raus:"  pstats->sum_cars_in " / " pstats->sum_cars_out
}

FUNCTION writeFinalStatsToFile (const stats *pstats){
    char filename [50];
    int counter = 1;

    WHILE file already exists
        counter++
        filename = "final_stats_" counter ".txt"
    END WHILE

    CREATE new file with filename

    WRITE final stats to file:
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            pstats->sum_parkhaus_auslastung/SIMULATION_TIME
            "Länge Warteschlange Ø:"            pstats->sum_length_queue/SIMULATION_TIME
            "Max. Länge Warteschlange:"         pstats->max_length_queue
            "Wartezeit Ø:"                      IF pstats->sum_cars_in > 0 {pstats->sum_wait_time/pstats->sum_cars_in} ELSE 0
            "ges. Anzahl Fahrzeuge rein/raus:"  pstats->sum_cars_in " / " pstats->sum_cars_out
    CLOSE file
}
 */
