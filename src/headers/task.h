#include "string.h"
typedef struct Task
{
    int hours;
    int minutes;
    char command[50];
    int info;
    struct Task * next;
} task;