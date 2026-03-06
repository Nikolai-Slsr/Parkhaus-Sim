#include "../include/sim_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
FUNCTION sim_parameters *get_inputs(){


   // This function is very repetitive all inputs follow the same pattern:
        * get the input from the user
        * convert the input to the correct type
        * check if the conversion was successful and if the value is valid
        * check if the value is in the valid range
        * if any of the checks fail, free the allocated sim_parameters struct to avoid memory leaks
        * if it makes sense, print an error message




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
    IF max_parking_spaces <= 0 THEN
        PRINT "Maximum number of parking spaces must be greater than 0. \n"
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
    IF max_parking_time <= 0 THEN
        PRINT "Maximum parking time must be greater than 0. \n"
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
    IF time_steps <= 0 THEN
        PRINT "Total number of time steps must be greater than 0. \n"
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL
    END IF
    sim_parameters->time_steps = the converted integer value


    PRINT "Enter the arrival probability (0-100): \n"
    prompt the user for arrival_probability and save the input
    convert the input string to a integer
    IF the conversion fails THEN
        free the allocated sim_parameters struct to avoid memory leaks
        RETURN NULL
    END IF
    IF arrival_probability is less than 0 OR greater than 100 THEN
        PRINT "Arrival probability must be between 0 and 100. \n"
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

sim_parameters *get_inputs(){

    sim_parameters *p_inputs = malloc(sizeof(sim_parameters));
    if (p_inputs == NULL) 
    {
        return NULL;
    }



    printf("Enter the maximum number of parking spaces: \n");
    char input_buffer[100];
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) 
    {
        free(p_inputs);
        return NULL;
    }

    int max_parking_spaces = strtol(input_buffer, NULL, 10);

    if (max_parking_spaces <= 0) 
    {
        printf("Maximum number of parking spaces must be greater than 0. \n");
        free(p_inputs);
        return NULL;
    }
    p_inputs->max_parking_spaces = max_parking_spaces;

    

    printf("Enter the maximum parking time for a vehicle: \n");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) 
    {
        free(p_inputs);
        return NULL;
    }

    int max_parking_time = strtol(input_buffer, NULL, 10);

    if (max_parking_time <= 0) 
    {
        printf("Maximum parking time must be greater than 0. \n");
        free(p_inputs);
        return NULL;
    }
    p_inputs->max_parking_time = max_parking_time;



    printf("Enter the total number of time steps for the simulation: \n");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) 
    {
        free(p_inputs);
        return NULL;
    }

    int time_steps = strtol(input_buffer, NULL, 10);

    if (time_steps <= 0) 
    {
        printf("Total number of time steps must be greater than 0. \n");
        free(p_inputs);
        return NULL;
    }
    p_inputs->time_steps = time_steps;



    printf("Enter the arrival probability (0-100): \n");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) 
    {
        free(p_inputs);
        return NULL;
    }

    int arrival_probability = strtol(input_buffer, NULL, 10);

    if (arrival_probability < 0 || arrival_probability > 100) 
    {
        printf("Arrival probability must be between 0 and 100. \n");
        free(p_inputs);
        return NULL;
    }
    p_inputs->arrival_probability = arrival_probability;



    printf("Enter the random seed for the simulation: \n");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) 
    {
        free(p_inputs);
        return NULL;
    }

    int rand_seed = strtol(input_buffer, NULL, 10);

    p_inputs->rand_seed = rand_seed;

    return p_inputs;
}