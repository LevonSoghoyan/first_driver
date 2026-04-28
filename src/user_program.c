#include <stdio.h>
#include <unistd.h>
#include "user_functions.h"
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024 
int main (int argc, char *argv[]) 
{
    if (argc == 1) {
        help();
    } else if (argc > 3) {
        dev(argv[1], argv[2], atoi(argv[3]));
    } else
        printf("Invalid command, Use ./user_program \n");
    return 0;   
}
