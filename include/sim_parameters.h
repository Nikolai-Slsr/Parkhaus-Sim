#ifndef SIM_INPUTS_H
#define SIM_INPUTS_H

typedef struct sim_parameters { // Struct to hold the simulation parameters that are required for the simulation
    int max_parking_spaces; // Maximum number of parking spaces
    int max_parking_time; // Maximum parking time for a vehicle
    int time_steps; // Total number of time steps for the simulation
    int arrival_probability; // Probability of a vehicle arriving at the parking lot in each time step (0-100)
    int rand_seed; // Random seed for generating random numbers, to allow for reproducibility of the simulation results
}sim_parameters;


/**
 * @brief Reads the simulation inputs from the user
 * 
 * Gets the simulation parameters from the user and returns it as a SimInputs struct. 
 * 
 * @return SimInputs Pointer to the struct containing the simulation parameters, NULL if there was an error during input reading or conversion
 */
sim_parameters *get_inputs();

#endif // SIM_INPUTS_H