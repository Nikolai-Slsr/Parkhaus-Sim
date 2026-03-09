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
int get_int(const char *prompt, int min, int max) { 
    char input_buffer[100];
    int value = 0;

    while (1) { // Loop until valid input is received
        printf("%s", prompt);                                               // Display the prompt to the user
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {     // Read input from the user
            fprintf(stderr, "Error reading input. Please try again.\n");
            continue;
        }

        char *endptr;                                                       //pointer to the first character that could not be converted -> shoulf be \n if the entire input was a valid integer
        value = strtol(input_buffer, &endptr, 10);

        if (*endptr != '\n') {                                              // Check if the conversion was successful and if the entire input was a valid integer
            fprintf(stderr, "Invalid input. Please enter a valid integer.\n");
            continue;
        }

        
        if (min = -1)
        {
            if (value > max) {                                   // Check if the value is in the valid range
                fprintf(stderr, "Input must be samller than %d. Please try again.\n", max);
                continue;
            }
        }
        else if (max = -1)
        {
            if (value < min) {                                   // Check if the value is in the valid range
                fprintf(stderr, "Input must be greater than %d. Please try again.\n", min);
                continue;
            }
        }
        else
        {
            if (value < min || value > max) {                                   // Check if the value is in the valid range
                fprintf(stderr, "Input must be between %d and %d. Please try again.\n", min, max);
                continue;
            }
        }
        break;
    }

    return value;
}

sim_parameters *get_inputs(){

    sim_parameters *p_inputs = malloc(sizeof(sim_parameters));
    if (p_inputs == NULL) 
    {
        return NULL;
    }

    p_inputs->time_steps = get_int("Enter the total number of time steps for the simulation: \n", 1, -1); //max set to -1 to indicate that there is no maximum value for this parameter

    p_inputs->max_parking_spaces = get_int("Enter the maximum number of parking spaces: \n", 1, -1); //max set to -1 to indicate that there is no maximum value for this parameter

    p_inputs->max_parking_time = get_int("Enter the maximum parking time for a vehicle: \n", 1, -1); //max set to -1 to indicate that there is no maximum value for this parameter

    p_inputs->arrival_probability = get_int("Enter the arrival probability (0-100): \n", 0, 100); //min set to 0 and max set to 100 to indicate that the value must be between 0 and 100

    p_inputs->rand_seed = get_int("Enter the random seed for the simulation: \n", -1, -1); //min and max set to -1 to indicate that there is no minimum or maximum value for this parameter

    return p_inputs;
}