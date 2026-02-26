#include <stdio.h>
#include <queue.h>
#include <parkhaus.h>


/**
 * static FILE *running_stats_file
 * 
 * FUNCTION updateStats (pstats, parked_cars, cars_in, cars_out, length_queue, last_wait_time){
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
    IF cars_in != 0 {
        pstats -> sum_wait_time += last_wait_time
    }
}

in the following, the print functions do not follow the intended visualization idea, just the concept.

FUNCTION printRuntimeStats (current_time, parked_cars, cars_in, cars_out, length_queue, car_in_queue, last_wait_time){
    PRINT:
            "Zeit seit Sim. Beginn:"    current_time
            "Parkhausauslastung:"       parked_cars "von" ANZAHL_STELLPLAETZE "Plaetze belegt"
            "Autos rein/raus:"          cars_in "/" cars_out
            "Laenge Warteschlange:"     length_queue "Autos + " car_in_queue "neue Autos"
            "Letzte Wartezeit:"         last_wait_time
}

FUNCTION createRunnningTimeStatsFile(){
    char filename [50];
    int counter = 1;

    WHILE file already exists
        counter++
        filename = "running_stats_" counter ".txt"
    END WHILE

    CREATE FILE with the name filename
    OPEN FILE filename for writing

    IF FILE filename IS NULL
        PRINT "Error: Could not create file" filename
    END IF

    PRINT "Created file: " filename
}

FUNCTION writeRunningTimeStatsToFile(int current_time, int parked_cars, int cars_in, int cars_out, int length_queue, int car_in_queue, int last_wait_time){
    WRITES TO FILE{
        //a table layout for every statistics parameter:
        Time stamp:     Parked cars:     new cars in:     cars out:    length queue:    cars in queue:   last wait time:

        //then writes the parameters into the table. every new timestep is a new line
        current_time    parked_cars      cars_in          cars_out     length_queue     car_in_queue     last_wait_time
        NEW LINE
        //this is not the right format, just the concept
    }
}

FUNCTION closeRunnningTimeStatsFile(){
    CLOSE open File
}

FUNCTION printFinalStats (const stats *pstats){
    PRINT:
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            pstats->sum_parkhaus_auslastung/SIMULATION_TIME
            "Länge Warteschlange Ø:"            pstats->sum_length_queue/SIMULATION_TIME
            "Max. Länge Warteschlange:"         pstats->max_length_queue
            "Wartezeit Ø:"                      pstats->sum_wait_time/pstats->all_cars_in
            "ges. Anzahl Fahrzeuge rein/raus:"  pstats->all_cars_in " / " pstats->all_cars_out
}

FUNCTION writeFinalStatsToFile (const stats *pstats){
    CREATE new file "statistics.txt" with random number
    IF file already exists THEN
        CREATE other file with new random number
    END IF
    WRITE final stats to file:
            "Simulationsdauer:"                 SIMULATION_TIME
            "Auslastung Parkhaus Ø:"            pstats->sum_parkhaus_auslastung/SIMULATION_TIME
            "Länge Warteschlange Ø:"            pstats->sum_length_queue/SIMULATION_TIME
            "Max. Länge Warteschlange:"         pstats->max_length_queue
            "Wartezeit Ø:"                      pstats->sum_wait_time/pstats->all_cars_in
            "ges. Anzahl Fahrzeuge rein/raus:"  pstats->all_cars_in " / " pstats->all_cars_out
    CLOSE file
}
 */
