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

//The following implementation doesn't 100% follow the pseudocode: We created an extra function to get inputs from the user, so get_inputs just calls get_int. This is a much better solution because it avoids a lot of repetative code and can be extended more easily.

*/

//define Colors and formating for the error messages in get_int

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
/** 
 * @brief Reads an integer input from the user with validation
 * 
 * Prompts the user for input and validates that it is an integer within the specified range. 
 * If the input is invalid, it will continue to prompt the user until a valid input is received.
 * 
 * @param[in] prompt The message to display to the user when asking for input
 * @param[in] min The minimum valid value for the input (inclusive), set to -1 if there is no minimum
 * @param[in] max The maximum valid value for the input (inclusive), set to -1 if there is no maximum
 * @param[out] stopped Pointer to a flag that is set to 1 if the user wants to stop the input process
 * @return int The validated integer input from the user
 */
static int get_int(const char *prompt, int min, int max, char *stopped) { //static because this function should not be called by other files
    char input_buffer[100];
    int value = 0;
    *stopped = 0; //initialize error to 0

    while (1) {                                                             // Loop until valid input is received
        printf("%s", prompt);                                               // Display the prompt to the user
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {     // Read input from the user
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Error reading input. Please try again.\n" ANSI_COLOR_RESET);    // I read that fprintf is better to print error messages, this is why we use it here
            continue;
        }
        if (strchr(input_buffer, '\n') == NULL) //this searches for the newline character in the input, if it is not found, it means that the user entered more characters than the buffer can hold --> we have to clear the input buffer and print an error message
        {
            while (getchar() != '\n'); //clear the input buffer by reading characters until we find the newline character
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Input too long. Please enter a shorter value.\n" ANSI_COLOR_RESET);
            continue;
        }
        

        char *endptr;                                                       // pointer to the first character that could not be converted -> shoulf be \n if the entire input was a valid integer
        value = strtol(input_buffer, &endptr, 10);

        if (*endptr != '\n' || *endptr == input_buffer[0]) {                // Check if the conversion was successful and if the entire input was a valid integer
            if (*endptr == 'q' || *endptr == 'Q')                           // If the user entered 'q' or 'Q', we exit the program so that so we dont have to use Strc + C to stop the program if the user is stuck in an infinite loop of invalid input
            {                                           
                fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Exiting the program.\n" ANSI_COLOR_RESET);
                *stopped = 1;
                return 0; // return 0; the value isnt important because it wont be used if stpped flag is set to 1
            }
            
            fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Invalid input. Please enter a valid integer.\n" ANSI_COLOR_RESET);
            continue;
        }

        if(min == -1 && max == -1)                              // If there is no minimum or maximum value, we can break the loop and return the value
        {                            
            break; // No need to check if the value is in the valid range since there is no range
        }
        else if (min == -1)                                     // If there is no minimum value, we only need to check if the value is less than the maximum value
        {
            if (value > max) {                                  // Check if the value is in the valid range
                fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Input must be smaller than %d. Please try again.\n" ANSI_COLOR_RESET, max);
                continue;
            }
        }
        else if (max == -1)                                     // If there is no maximum value, we only need to check if the value is greater than the minimum value
        {
            if (value < min) {                                  // Check if the value is in the valid range
                fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Input must be greater than %d. Please try again.\n" ANSI_COLOR_RESET, min);
                continue;
            }
        }
        else
        {
            if (value < min || value > max) {                    // Check if the value is in the valid range
                fprintf(stderr, ANSI_BOLD ANSI_COLOR_RED "Input must be between %d and %d. Please try again.\n" ANSI_COLOR_RESET, min, max);
                continue;
            }
        }
        break;
    }
    return value;
}

sim_parameters *get_inputs(){

    printf("Please enter the simulation parameters. Enter '" ANSI_BOLD ANSI_COLOR_RED "q" ANSI_COLOR_RESET "' to exit the program. \n"); // Nice Header and instruction on how to exit entering the parameters

    sim_parameters *p_inputs = malloc(sizeof(sim_parameters));
    if (p_inputs == NULL) 
    {
        return NULL;
    }

    char stopped = 0; // This flag will be set to 1 if the user wants to stop the input process

    p_inputs->time_steps = get_int("Enter the total number of time steps for the simulation: \n", 1, -1, &stopped); //max set to -1 to indicate that there is no maximum value for this parameter
    if (stopped == 1) 
    {
        free(p_inputs);
        return NULL;
    }
    
    p_inputs->max_parking_spaces = get_int("Enter the maximum number of parking spaces: \n", 1, -1, &stopped); //max set to -1 to indicate that there is no maximum value for this parameter
    if (stopped == 1) 
    {
        free(p_inputs);
        return NULL;
    }

    p_inputs->max_parking_time = get_int("Enter the maximum parking time for a vehicle: \n", 1, -1, &stopped); //max set to -1 to indicate that there is no maximum value for this parameter
    if (stopped == 1) 
    {
        free(p_inputs);
        return NULL;
    }

    p_inputs->arrival_probability = get_int("Enter the arrival probability (0-100): \n", 0, 100, &stopped); //min set to 0 and max set to 100 to indicate that the value must be between 0 and 100
    if (stopped == 1) 
    {
        free(p_inputs);
        return NULL;
    }

    p_inputs->rand_seed = get_int("Enter the random seed for the simulation: \n", -1, -1, &stopped); //min and max set to -1 to indicate that there is no minimum or maximum value for this parameter
    if (stopped == 1) 
    {
        free(p_inputs);
        return NULL;
    }
    
    return p_inputs;
}