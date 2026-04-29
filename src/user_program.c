#include <stdio.h>
#include <unistd.h>
#include "user_functions.h"
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

/* Marcos */
#define BUFFER_SIZE 1024 

/******************************************************************************
 * @brief Main entry point: validates command-line arguments and tests device functionality.
 *
 * @param argc   The number of command-line arguments provided.
 * @param argv   An array of strings representing the command-line arguments.
 *
 * @return int   Returns 0 if the program completes successfully, 
 * or a non-zero error code if validation fails.
 *****************************************************************************/
int main(int argc, char *argv[]) 
{
    if (argc == 1) {
        help();
    } else if (argc > 3) {
        dev(argv[1], argv[2], atoi(argv[3]));
    } else {
        printf("Invalid command, Use ./user_program \n");
    }

    return 0;
}
