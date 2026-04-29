#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "user_functions.h"

/* Macross */
#define BUF_SIZE 1024

char buf[BUF_SIZE];

/******************************************************************************
 * @brief Displays the help menu and command usage information to the console.
 *****************************************************************************/
void help()
{
    printf("\nUsage\n\n");
    printf("./user_program   --> Show this massage\n");
    printf("./user_program  <Device path>   <File path> <len> to read len characters whit device to File and show in CMD\n");
}

/******************************************************************************
 * @brief Opens a file and writes a specified number of characters to the device.
 *
 * @param pDevice Path to the destination device node.
 * @param pFile   Path to the source file containing the data.
 * @param len     The number of characters to be transferred.
 *
 * @return int    Returns 1 if the operation is successful, otherwise 0.
 *****************************************************************************/
int dev(char *pDevice, char *pFile, int len)
{
    /* Opening Device and file */
    int Dev_fd = open(pDevice,O_RDWR);
    int File_fd = open(pFile, O_RDWR);

    /* Error handling */
    if (Dev_fd < 0) {
        printf("ERROR: Failed to open '%s'.\n", pDevice);
        return 0;
    }

    if (File_fd < 0) {
        printf("ERROR: Failed to open '%s'.\n", pFile);
        return 0;
    }
    
    /* Reading in device and print in terminal */
    int Copyed_Count = read(File_fd, buf, len);
    Copyed_Count = write(Dev_fd, buf, Copyed_Count);
    read(Dev_fd, buf, Copyed_Count);
    printf("%s \n", buf);

    /* Closing device and file */
    close(File_fd);
    close(Dev_fd);

    return 1;
}

