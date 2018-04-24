#include "headers/task.h"
#include <stdio.h>

task* AddToEmpty(task* first, int hour, int minutes, char* command, int info)
{    
    task* tmp = malloc(sizeof(task));
    tmp->hour = hour;
    tmp->minutes = minutes;
    strcpy(tmp->command, command);
    tmp->info = info;
    first = tmp;
    first->next = first;

    return first;
}

task* Add(task* first, int hour, int minutes, char* command, int info)
{   
    if(first == NULL)
    {
        first = AddToEmpty(first, hour, minutes, command, info);
    }
    else
    {
        task *tmp, *p;
        p = first;
        while(p->next->hour < hour)
        {
            if(p->next == first)
                break;
            p = p->next;
        }
        
        if(p->next->hour == hour)
        {
            while(p->next->minutes < minutes)
            {
                if(p->next == first)
                    break;
                p = p->next;
            }

        }
        
        tmp = (task*)malloc(sizeof(task));
        tmp->hour = hour;
        tmp->minutes = minutes;
        strcpy(tmp->command, command);
        tmp->info = info;
        tmp->next = p->next;
        p->next = tmp;
    }    
    return first;
}

int SleepTime(task* task)
{
    double seconds;
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    timeinfo->tm_hour = task->hour;
    timeinfo->tm_min = task->minutes;
    timeinfo->tm_sec = 0;
    seconds = difftime(mktime(timeinfo),now);
    return ((int) seconds);
}

task* KindOfSort(task* first)
{
    task* tmp, *tmp2, *tmp3;
    tmp = first;
    tmp2 = first;
    tmp3 = first;
    while(tmp->next != first)
    {
        if((SleepTime(tmp->next)-SleepTime(first)) > 0 && (SleepTime(tmp)-SleepTime(first)) < 0)
        {
            if(tmp->hour < first->hour)
            tmp2 = tmp;
            tmp = tmp->next;
            while(tmp3->next != first)
            {
                tmp3 = tmp3->next;
            }
            tmp3->next = first->next;
            tmp2->next = first;
            first->next = tmp;
            break;
        }
    tmp = tmp->next;
    }
    while (SleepTime(first->next)-SleepTime(first) > 0)
        first = first->next;
    return first->next;
}

task* DeleteList(task* first)
{
    task* current = first;
    task* next;
    while(current->next != first)
    {
        next = current->next;
        free(current);
        current = next;
    }
    first = NULL;
    return first;
}