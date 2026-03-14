#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdio.h>
#include "sim_parameters.h"
/**
 * @struct
 * @brief stores statistic values
 */
typedef struct {
    FILE *p_running_stats_file;         //pointer to a FILE

    int max_wait_time;                  //maximum wait time for a car before it could park
    int sum_parking_occupancy;          //sum of occupancy of the parking garage. Needed for calculations of average
    int sum_queue_length;               //sum of queue length to calclulate average queue length
    int max_queue_length;               //maximum queue length
    int sum_wait_time;                  //sum of all waiting times of the cars in queue to calculate average
    int sum_cars_entered;               //sum of all cars that drove into the garage
    int sum_cars_exited;                //sum of all cars that left the garage

    int current_time;                   //current simulation time step since start of the simulation
    int parked_car_count;               //Number of currently parked cars
    int cars_entered;                   //Number of cars that entered the parking garage during the current time step
    int cars_exited;                    //Number of cars that left the parking garage during the current time step
    int queue_length;                   //Current number of cars waiting in the queue
    int new_cars_in_queue;              //Number of newly arrived cars added to the queue during this time step
    int last_wait_time;                 //Waiting time of the car that parked during this time step

}stats;


/**
 * @brief       updates the dynamic statistics after each time step
 * 
 * this funtion updates a max value if the new value is higher than the max value.
 * it also calculates the sums of every important statistics parameter and saves it to a struct via pointer
 * 
 * @param[in]   p_stats             pointer to struct stats that stores statistic values
 * @param[in]   parked_car_count    Number of currently parked cars
 * @param[in]   cars_entered        Number of cars that entered the parking garage during the current time step
 * @param[in]   cars_exited         Number of cars that left the parking garage during the current time step
 * @param[in]   queue_length        Current number of cars waiting in the queue
 * @param[in]   last_wait_time      Waiting time of the car that parked during this time step, 0 if no car drove into Parkhaus
 * @param[in]   current_time        current simulation time step since start of the simulation
 * @param[in]   new_cars_in_queue   Number of newly arrived cars added to the queue during this time step
 * 
 * @return       this function does not return a value
 */
void updateStats(stats *p_stats, int parked_car_count, int cars_entered, int cars_exited, int queue_length, int last_wait_time, int current_time, int new_cars_in_queue);


/**
 * @brief       prints run time statistics
 * 
 * this function takes the current variables for the statistics and prints it in the Terminal
 * 
 * @param[in]   stats               struct with dynmaic statistic values collected during simulation 
 * 
 * @return      this function does not return a value
*/
void printRuntimeStats(const stats *p_stats, const sim_parameters *p_sim_parameters);

/**
 * @brief       creates file to write runnning time stats into it
 * 
 * this function creates a new .txt file in which the running time statistics can be written into
 * the file is stored 
 */
void createRunningTimeStatsFile(stats *p_stats);

/**
 * @brief       writes running statistics to file
 * 
 * this function gets all the running statistic parameters and writes them into a file
 * after each timestep. all running statistics will be written into one file
 * 
 * @param[in]   stats               struct with dynmaic statistic values collected during simulation 
 * 
 * @return      this function does not return a value
 */
void writeRunningTimeStatsToFile(const stats *p_stats);

/**
 * @brief   closes running time statistics file
 * 
 * @param[in]   stats               struct with dynmaic statistic values collected during simulation
 * 
 * @return      this function does not return a value
 */
void closeRunningTimeStatsFile(stats *p_stats);

/**
 * @brief       prints final statistics
 * 
 * this function takes the statistics parameters that were saved in the struct stats and prints the final statistics in the terminal
 * it also calculates the average values based on the Simulation time
 * 
 * @param[in]   stats               struct with dynmaic statistic values collected during simulation 
 * 
 * @return      this function does not return a value
 */
void printFinalStats(const stats *p_stats, const sim_parameters *p_sim_parameters);

/**
 * @brief       writes final statistics to file
 * 
 * this function creates a new file, takes the statistics parameters that were saved in the struct stats
 * it also calculates the average values based on the Simulation time
 * and prints the final statistics into the new file
 * 
 * @param[in]   stats               struct with dynmaic statistic values collected during simulation 
 * 
 * @return       this function does not return a value
 */
void writeFinalStatsToFile(const stats *p_stats, const sim_parameters *p_sim_parameters);

#endif 
