#include <stdio.h>
#include "../include/statistics.h"
#include "../include/parkhaus.h"
#include "../include/sim_parameters.h"

 void updateStats (stats *pstats, int parked_cars, int cars_in, int cars_out, int length_queue, int last_wait_time, int current_time, int car_in_queue){
    if (last_wait_time > pstats -> max_wait_time){
        pstats -> max_wait_time = last_wait_time;
    }
    if (length_queue > pstats -> max_length_queue) {
        pstats -> max_length_queue = length_queue;
    }
    pstats -> sum_cars_in += cars_in;
    pstats -> sum_cars_out += cars_out;
    
    pstats -> sum_parkhaus_auslastung += parked_cars;
    pstats -> sum_length_queue += length_queue;
    if (last_wait_time > 0){
        pstats -> sum_wait_time += last_wait_time;
    }

    pstats -> current_time = current_time;
    pstats -> parked_cars = parked_cars;
    pstats -> cars_in = cars_in;
    pstats -> cars_out = cars_out;
    pstats -> length_queue = length_queue;
    pstats -> car_in_queue = car_in_queue;
    pstats -> last_wait_time = last_wait_time;
    }

void printRuntimeStats (const stats *pstats, const sim_parameters *pSim_parameters){
    
    printf ("\n\n|");
    for (int i=0; i<100; i++){
        printf("=");
    }
    printf ("|");

    printf("\n\n%-25s %-d", "Zeit seit Sim.Beginn:", pstats -> current_time);
    printf("\n%-25s %-5d von %d Plaetze belegt", "Parkhausauslastung:", pstats -> parked_cars, pSim_parameters->max_parking_spaces);
    printf("\n%-25s %-d / %d", "Autos rein/raus: ", pstats -> cars_in, pstats -> cars_out);
    printf("\n%-25s %-5d Autos + %u neue Autos", "Laenge Warteschlange:", pstats -> length_queue, pstats -> car_in_queue);
    if(pstats->last_wait_time == -1){
        printf("\n%-25s %c", "Letzte Wartezeit:", '-');
    }else{
        printf("\n%-25s %-d", "Letzte Wartezeit:", pstats -> last_wait_time);
    }

    printf ("\n|");
    for (int i=0; i<100; i++){
        printf("=");
    }
}

void createRunningTimeStatsFile(stats *pstats){
    char filename [50];
    int counter = 1;

    while (1){
        sprintf(filename, "running_stats_%d.txt", counter);
        FILE *checkfile = fopen(filename, "r");
    
        if (checkfile == NULL){
            break;
        } else {
            fclose (checkfile);
        }
        counter ++;
    }
    pstats->running_stats_file = fopen(filename, "w");
    fprintf(pstats->running_stats_file, "%-14s %-15s %-15s %-12s %-16s %-17s %-18s",
        "Time stamp: |", "Parked cars: |", "new cars in: |", "cars out: |", "length queue: |", "cars in queue: |", "last wait time: |");
    printf("Created file: %s", filename);
}

void writeRunningTimeStatsToFile(const stats *pstats){
    fprintf(pstats->running_stats_file, "\n%-12u%-2c %-13u%-2c %-13u%-2c %-10u%-2c %-14u%-2c %-15u%-2c %-16u%-2c", 
        pstats -> current_time, '|', pstats -> parked_cars, '|', pstats -> cars_in, '|', pstats -> cars_out, '|', pstats -> length_queue, '|', pstats -> car_in_queue, '|', pstats -> last_wait_time, '|');
}

void closeRunningTimeStatsFile(stats *pstats){
    if (pstats->running_stats_file != NULL){
        fclose(pstats->running_stats_file);
        pstats->running_stats_file = NULL;
    }
}

void printFinalStats (const stats *pstats, const sim_parameters *pSim_parameters){

    printf ("\n\n|");
    for (int i=0; i<100; i++){
        printf("=");
    }
    printf ("|");

    printf("\n\n%-35s %-40u", "Simulationsdauer:", pSim_parameters->time_steps);
    if (pSim_parameters->time_steps != 0){
        printf("\n%-35s %-40u%c", "Auslastung Parkhaus Ø:", pstats->sum_parkhaus_auslastung/pSim_parameters->time_steps, '%');
        printf("\n%-35s %-40u Autos", "Länge Warteschlange Ø:", pstats->sum_length_queue/pSim_parameters->time_steps);
    }else {
        printf("\n%-35s %-40u%c", "Auslastung Parkhaus Ø:", 0, '%');
        printf("\n%-35s %-40u Autos", "Länge Warteschlange Ø:", 0);
    }
    printf("\n%-35s %-40u Autos", "Max. Laenge Warteschlange:", pstats->max_length_queue);
    double avg_wait_time;
    if (pstats->sum_cars_in > 0) {
        avg_wait_time = pstats->sum_wait_time/pstats->sum_cars_in;
    } else {
        avg_wait_time = 0.0;
    }
    printf("\n%-35s %-40f minuten", "Wartezeit Ø:", avg_wait_time);
    printf("\n%-35s +%-40u/-%u", "ges. Anzahl Fahrzeuge rein/raus:", pstats->sum_cars_in, pstats->sum_cars_out);

    printf ("\n|");
    for (int i=0; i<100; i++){
        printf("=");
    }
    printf ("|");
}

void writeFinalStatsToFile (const stats *pstats, const sim_parameters *pSim_parameters){
    char filename [50];
    int counter = 1;

    while (1){
        sprintf(filename, "final_stats_%d.txt", counter);
        FILE *checkfile = fopen(filename, "r");
    
        if (checkfile == NULL){
            break;
        } else {
            fclose (checkfile);
        }
        counter ++;
    }
    FILE *final_stats = fopen (filename, "w");

    fprintf (final_stats,"\n\n|");
    for (int i=0; i<100; i++){
        fprintf(final_stats,"=");
    }
    fprintf (final_stats,"|");

    fprintf(final_stats,"\n\n%-35s %-40u", "Simulationsdauer:", pSim_parameters->time_steps);
    if (pSim_parameters->time_steps != 0){
        fprintf(final_stats,"\n%-35s %-40u%c", "Auslastung Parkhaus Ø:", pstats->sum_parkhaus_auslastung/pSim_parameters->time_steps, '%');
        fprintf(final_stats,"\n%-35s %-40u Autos", "Länge Warteschlange Ø:", pstats->sum_length_queue/pSim_parameters->time_steps);   
    }else {
        fprintf(final_stats,"\n%-35s %-40u%c", "Auslastung Parkhaus Ø:", 0, '%');
        fprintf(final_stats,"\n%-35s %-40u Autos", "Länge Warteschlange Ø:", 0); 
    }
    fprintf(final_stats,"\n%-35s %-40u Autos", "Max. Laenge Warteschlange:", pstats->max_length_queue);
    int avg_wait_time;
    if (pstats->sum_cars_in > 0) {
        avg_wait_time = pstats->sum_wait_time/pstats->sum_cars_in;
    } else {
        avg_wait_time = 0;
    }
    fprintf(final_stats,"\n%-35s %-40u minuten", "Wartezeit Ø:", avg_wait_time);
    fprintf(final_stats,"\n%-35s +%-40u/-%u", "ges. Anzahl Fahrzeuge rein/raus:", pstats->sum_cars_in, pstats->sum_cars_out);

    fprintf (final_stats,"\n|");
    for (int i=0; i<100; i++){
        fprintf(final_stats,"=");
    }
    fprintf (final_stats,"|");

    fclose(final_stats);
}
