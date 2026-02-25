#ifndef STATISTICS_H
#define STATISTICS_H

/**
 * @struct
 * @brief stores statistic values
 */
typedef struct {
    int max_wait_time
    int sum_parkhaus_auslastung
    int sum_length_queue
    int max_length_queue
    int sum_wait_time
    int all_cars_in
    int all_cars_out
}stats;


/**
 * @brief       updates the dynamic statistics after each time step
 * 
 * this funtion updates a max value if the new value is higher than the max value.
 * it also calculates the sums of every important statistics parameter and saves it to a struct via pointer
 * 
 * @param[in]   pstats              pointer to struct stats that stores statistic values
 * @param[in]   parked_cars         Number of currently parked cars
 * @param[in]   cars_in             Number of cars that entered the parking garage during the current time step
 * @param[in]   cars_out            Number of cars that left the parking garage during the current time step
 * @param[in]   length_queue        Current number of cars waiting in the queue
 * @param[in]   last_wait_time      Waiting time of the car that parked during this time step
 * 
 * @return       this function does not return a value
 */
void updateStats(stats *pstats, int parked_cars, int cars_in, int cars_out, int length_queue, int last_wait_time);


/**
 * @brief       prints run time statistics
 * 
 * this function takes the current variables for the statistics and prints it in the Terminal
 * 
 * @param[in]   current_time        current simulation time step since start of the simulation
 * @param[in]   parked_cars         Number of currently parked cars
 * @param[in]   cars_in             Number of cars that entered the parking garage during the current time step
 * @param[in]   cars_out            Number of cars that left the parking garage during the current time step
 * @param[in]   length_queue        Current number of cars waiting in the queue
 * @param[in]   car_in_queue        Number of newly arrived cars added to the queue during this time step
 * @param[in]   last_wait_time      Waiting time of the car that parked during this time step
 * 
 * 
 * @return      this function does not return a value
*/
void printRuntimeStats(int current_time, int parked_cars, int cars_in, int cars_out, int length_queue, int car_in_queue, int last_wait_time);

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
void printFinalStats(const stats *pstats);

/**
 * @brief       writes final statistics to file
 * 
 * this function creates a new file, takes the statistics parameters that were saved in the struct stats
 * it also calculates the average values based on the Simulation time
 * and prints the final statistics into the new file
 * 
 * @param[in]   stats               struct with dynmaic statistic values collected during simulation 
 * 
 * return       this function does not return a value
 */
writeStatsToFile(const stats *pstats);

#endif 