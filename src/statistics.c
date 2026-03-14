/*
 * File: statistics.c
 * Description: Updates and prints simulation statistics.
 * Tracks running values and generates final statistics output.
 */

#include <stdio.h>
#include <sys/stat.h>
#include "../include/statistics.h"
#include "../include/parkhaus.h"
#include "../include/sim_parameters.h"
#include "../include/format_def.h"



 void updateStats (stats *p_stats, int parked_car_count, int cars_entered, int cars_exited, int queue_length, int last_wait_time, int current_time, int new_cars_in_queue){
    if (last_wait_time > p_stats -> max_wait_time){
        p_stats -> max_wait_time = last_wait_time;
    }
    if (queue_length > p_stats -> max_queue_length) {
        p_stats -> max_queue_length = queue_length;
    }
    p_stats -> sum_cars_entered += cars_entered;
    p_stats -> sum_cars_exited += cars_exited;
    
    p_stats -> sum_parking_occupancy += parked_car_count;
    p_stats -> sum_queue_length += queue_length;
    if (last_wait_time > 0){
        p_stats -> sum_wait_time += last_wait_time;
    }

    p_stats -> current_time = current_time;
    p_stats -> parked_car_count = parked_car_count;
    p_stats -> cars_entered = cars_entered;
    p_stats -> cars_exited = cars_exited;
    p_stats -> queue_length = queue_length;
    p_stats -> new_cars_in_queue = new_cars_in_queue;
    p_stats -> last_wait_time = last_wait_time;

    }

void printRuntimeStats (const stats *p_stats, const sim_parameters *p_sim_parameters){
    
    printf ("\n\n|");
    for (int i=0; i<60; i++){
        printf("=");
    }
    printf ("|");

    printf("\n\n%-25s %-d Minuten", "Zeit seit Sim.Beginn:", p_stats -> current_time);
    printf("\n%-25s" ANSI_BOLD" %-d" ANSI_COLOR_RESET " von " ANSI_BOLD "%d" ANSI_COLOR_RESET " belegt", "Parkhausauslastung:", p_stats -> parked_car_count, p_sim_parameters->max_parking_spaces);
    
    printf("\n%-26s", "Auslastung in Prozent:");
    int occupancy_percent = 0;
    int occupancy_bar_length = 30;
    int filled_length = 0;
    if (p_sim_parameters->max_parking_spaces > 0){
        occupancy_percent = (int)((double)p_stats->parked_car_count / p_sim_parameters->max_parking_spaces * 100);
        printf("%d%% ", occupancy_percent);
        filled_length = occupancy_bar_length * occupancy_percent / 100;
        for (int i = 0; i < filled_length; i++) {
            printf(ANSI_COLOR_GREEN "■" ANSI_COLOR_RESET);
        }
        for (int i = filled_length; i < occupancy_bar_length; i++) {
            printf(ANSI_COLOR_RED "□" ANSI_COLOR_RESET);
        }
    } else {
        printf("0%%  ");
    }

    printf("\n%-25s" ANSI_COLOR_GREEN " +%-d" ANSI_COLOR_RESET "/" ANSI_COLOR_RED"-%d" ANSI_COLOR_RESET, "Autos rein/raus: ", p_stats -> cars_entered, p_stats -> cars_exited);
    if(p_stats->new_cars_in_queue == 1)
    {
        printf("\n%-25s %-d Autos " ANSI_COLOR_GREEN"%+d" ANSI_COLOR_RESET, "Laenge Warteschlange:", p_stats -> queue_length, p_stats -> new_cars_in_queue);
    }else if(p_stats->new_cars_in_queue == -1)
    {
        printf("\n%-25s %-d Autos " ANSI_COLOR_RED"%+d" ANSI_COLOR_RESET, "Laenge Warteschlange:", p_stats -> queue_length, p_stats -> new_cars_in_queue);
    }else if(p_stats->new_cars_in_queue == 0)
    {
        printf("\n%-25s %-d Autos %+d", "Laenge Warteschlange:", p_stats -> queue_length, p_stats -> new_cars_in_queue);
    }
    if(p_stats->last_wait_time == -1){
        printf("\n%-25s %c", "Letzte Wartezeit:", '-');
    }else{
        printf("\n%-25s %-d Minuten", "Letzte Wartezeit:", p_stats -> last_wait_time);
    }
}

void createRunningTimeStatsFile(stats *p_stats){
    char filename [50];
    int file_counter = 1;
    struct stat output_directory_status = {0};

    if (stat("outputs", &output_directory_status) == -1) //check if folder 'Outputs' exists. If not create the folder
    {
        mkdir("outputs", 0777);
    }

    while (1){
        sprintf(filename, "outputs/running_stats_%d.txt", file_counter);
        FILE *p_check_file = fopen(filename, "r");
    
        if (p_check_file == NULL){
            break;
        } else {
            fclose (p_check_file);
        }
        file_counter ++;
    }
    p_stats->p_running_stats_file = fopen(filename, "w");
    fprintf(p_stats->p_running_stats_file, "%-17s %-16s %-15s %-12s %-16s %-17s",
        "|  Time stamp: |", "Parked cars:  |", "new cars in: |", "cars out: |", "length queue: |", "last wait time: |");

    printf("Created file: %s", filename);
    }

void writeRunningTimeStatsToFile(const stats *p_stats){
    fprintf(p_stats->p_running_stats_file, "\n%-3c%-12d%-2c %-14d%-2c %-13d%-2c %-10d%-2c %-2d %c%+d%-8c%-3c", 
        '|', p_stats -> current_time, '|', p_stats -> parked_car_count, '|', p_stats -> cars_entered, '|', p_stats -> cars_exited, '|', p_stats -> queue_length, '(', p_stats -> new_cars_in_queue,')', '|');
    if (p_stats->last_wait_time == -1){
        fprintf(p_stats->p_running_stats_file, "%-16c%-2c", '-', '|');
    }else{
        fprintf(p_stats->p_running_stats_file, "%-16d%-2c", p_stats -> last_wait_time, '|');
    }
}

void closeRunningTimeStatsFile(stats *p_stats){
    if (p_stats->p_running_stats_file != NULL){
        fclose(p_stats->p_running_stats_file);
        p_stats->p_running_stats_file = NULL;
    }
}

void printFinalStats (const stats *p_stats, const sim_parameters *p_sim_parameters){

    printf ("\n\n|");
    for (int i=0; i<16; i++){
        printf("=");
    }
    printf("FINAL SIMULATION STATISTICS");
    for (int i=0; i<17; i++){
        printf("=");
    }
    printf ("|");

    double average_occupancy_percent =  (double)p_stats->sum_parking_occupancy / (p_sim_parameters->time_steps * p_sim_parameters->max_parking_spaces) * 100;

    printf("\n\n%-35s %d Minuten", "Simulationsdauer:", p_sim_parameters->time_steps);
    if (p_sim_parameters->time_steps != 0){
        printf("\n%-36s %.2f%%", "Auslastung Parkhaus Ø:", average_occupancy_percent);
        printf("\n%-37s %.2f Autos", "Länge Warteschlange Ø:", (double)p_stats->sum_queue_length / p_sim_parameters->time_steps);
    }else {
        printf("\n%-36s %.2f%%", "Auslastung Parkhaus Ø:", 0.00);
        printf("\n%-37s %d Autos", "Länge Warteschlange Ø:", 0);
    }
    printf("\n%-35s %d Autos", "Max. Laenge Warteschlange:", p_stats->max_queue_length);
    double avg_wait_time;
    if (p_stats->sum_cars_entered > 0) {
        avg_wait_time = (double)p_stats->sum_wait_time / p_stats->sum_cars_entered;
    } else {
        avg_wait_time = 0.0;
    }
    printf("\n%-36s %.2f Minuten", "Wartezeit Ø:", avg_wait_time);
    printf("\n%-35s" ANSI_COLOR_GREEN " +%d"ANSI_COLOR_RESET "/" ANSI_COLOR_RED"-%d"ANSI_COLOR_RESET, "ges. Anzahl Fahrzeuge rein/raus:", p_stats->sum_cars_entered , p_stats->sum_cars_exited);

    printf ("\n\n|");
    for (int i=0; i<60; i++){
    printf("=");
    }
    printf("|\n");
}

void writeFinalStatsToFile (const stats *p_stats, const sim_parameters *p_sim_parameters){
    char filename [50];
    int file_counter = 1;
    struct stat output_directory_status = {0};

    if (stat("outputs", &output_directory_status) == -1) //check if folder 'Outputs' exists. If not create the folder
    {
        mkdir("outputs", 0777);
    }

    while (1){
        sprintf(filename, "outputs/final_stats_%d.txt", file_counter);
        FILE *p_check_file = fopen(filename, "r");
    
        if (p_check_file == NULL){
            break;
        } else {
            fclose (p_check_file);
        }
        file_counter ++;
    }
    FILE *p_final_stats = fopen (filename, "w");

    fprintf (p_final_stats,"\n\n|");
    for (int i=0; i<16; i++){
        fprintf(p_final_stats,"=");
    }
    fprintf(p_final_stats,"FINAL SIMULATION STATISTICS");
    for (int i=0; i<17; i++){
        fprintf(p_final_stats,"=");
    }
    fprintf (p_final_stats,"|");

    fprintf(p_final_stats,"\n\n%-35s %d Minuten", "Simulationsdauer:", p_sim_parameters->time_steps);

    double average_occupancy_percent =  (double)p_stats->sum_parking_occupancy / (p_sim_parameters->time_steps * p_sim_parameters->max_parking_spaces) * 100;

    if (p_sim_parameters->time_steps != 0){
        fprintf(p_final_stats,"\n%-36s %.2f%%", "Auslastung Parkhaus Ø:", average_occupancy_percent);
        fprintf(p_final_stats,"\n%-37s %.2f Autos", "Länge Warteschlange Ø:", (double)p_stats->sum_queue_length / p_sim_parameters->time_steps);   
    }else {
        fprintf(p_final_stats,"\n%-36s %.2f%%", "Auslastung Parkhaus Ø:", 0.00);
        fprintf(p_final_stats,"\n%-37s %d Autos", "Länge Warteschlange Ø:", 0); 
    }
    fprintf(p_final_stats,"\n%-35s %d Autos", "Max. Laenge Warteschlange:", p_stats->max_queue_length);
    double avg_wait_time;
    if (p_stats->sum_cars_entered > 0) {
        avg_wait_time = (double)p_stats->sum_wait_time / p_stats->sum_cars_entered;
    } else {
        avg_wait_time = 0;

    }
    fprintf(p_final_stats,"\n%-36s %.2f Minuten", "Wartezeit Ø:", avg_wait_time);
    fprintf(p_final_stats,"\n%-35s +%d/-%d", "ges. Anzahl Fahrzeuge rein/raus:", p_stats->sum_cars_entered, p_stats->sum_cars_exited);

    fprintf (p_final_stats,"\n\n|");
    for (int i=0; i<60; i++){
        fprintf(p_final_stats,"=");
    }
    fprintf (p_final_stats,"|");

    printf("Created file: %s\n\n", filename);

    fclose(p_final_stats);
}
