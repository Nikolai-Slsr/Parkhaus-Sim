#include "../include/sim_param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
FUNCTION sim_parameters *get_inputs(){
    sim_parameters = allocate memory for a sim_parameters struct
    IF memory allocation fails THEN
        RETURN NULL to indicate failure
    END IF

    PRINT "Enter the maximum number of parking spaces: \n"
    prompt the user for max_parking_spaces and save the input //use fgets to read the input as a string
    convert the input string to an integer // use string.h strtol function to convert the string to an integer
    IF the conversion fails THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL 
    END IF
    sim_parameters->max_parking_spaces = the converted integer value

    PRINT "Enter the maximum parking time for a vehicle: \n"
    prompt the user for max_parking_time and save the input
    convert the input string to an integer
    IF the conversion fails THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL 
    END IF 
    sim_parameters->max_parking_time = the converted integer value

    PRINT "Enter the total number of time steps for the simulation: \n"
    prompt the user for time_steps and save the input
    convert the input string to an integer
    IF the conversion fails THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL 
    END IF
    sim_parameters->time_steps = the converted integer value

    PRINT "Enter the arrival probability (0-1): \n"
    prompt the user for arrival_probability and save the input
    convert the input string to a double // use strtod function to convert the string to a double
    IF the conversion fails THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL 
    END IF
    IF arrival_probability is less than 0 OR greater than 1 THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL 
    END IF
    sim_parameters->arrival_probability = the converted double value

    PRINT "Enter the random seed for the simulation: \n"
    prompt the user for rand_seed and save the input
    convert the input string to an integer
    IF the conversion fails THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL 
    END IF
    sim_parameters->rand_seed = the converted integer value
    

    RETURN the pointer to the sim_parameters struct containing the user inputs
}

*/