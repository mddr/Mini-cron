#ifndef TASK_H
#define TASK_H

#include "string.h"
#include <stdlib.h>

typedef struct Task
{
    int hours;
    int minutes;
    char command[50];
    int info;
    struct Task * next;
} task;

task* AddToEmpty(task*, int, int, char*, int);
task* Add(task*, int, int, char*, int);

#endif