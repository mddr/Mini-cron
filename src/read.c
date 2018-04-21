#include "headers/read.h"

int GetFile(char* filename, int mode)
{
    int counter, i;
    int fd = open(filename, mode);

    if (fd == -1) {
        return -1;
    } else {
        return fd;
    }
}