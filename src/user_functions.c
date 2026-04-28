#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "user_functions.h"
#define BUF_SIZE 1024
char buf[BUF_SIZE];
void help()
{
    printf("\nUsage\n\n");
    printf("./user_program   --> Show this massage\n");
    printf("./user_program  <Device path>   <File path> <len> to read len characters whit device to File and show in CMD\n");
}
int dev(char *pDevice, char *pFile, int len)
{
    int Dev_fd = open(pDevice,O_RDWR);
    int File_fd = open(pFile, O_RDWR);
    if (Dev_fd < 0) {
        printf("ERROR: Failed to open '%s'.\n", pDevice);
        return 0;
    }
    if (File_fd < 0) {
        printf("ERROR: Failed to open '%s'.\n", pFile);
        return 0;
    }
    int Copyed_Count = read(File_fd, buf, len);
    Copyed_Count = write(Dev_fd, buf, Copyed_Count);
    read(Dev_fd, buf, Copyed_Count);
    printf("%s", buf);
    close(File_fd);
    close(Dev_fd);
    return 0;
}

