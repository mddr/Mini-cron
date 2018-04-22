#ifndef TASK_H
#define TASK_H

#include "string.h"
#include <stdlib.h>
#include <time.h>

typedef struct Task
{
    int hours;
    int minutes;
    char command[500];
    int info;
    struct Task * next;
} task;

task* AddToEmpty(task*, int, int, char*, int);
task* Add(task*, int, int, char*, int);
int SleepTime(task*);
task* KindOfSort(task*);
task* DeleteList(task*);

#endif