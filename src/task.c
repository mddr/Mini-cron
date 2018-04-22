#include "headers/task.h"
#include <stdio.h>

task* AddToEmpty(task* first, int hours, int minutes, char* command, int info)
{    
    task* tmp = malloc(sizeof(task));
    tmp->hours = hours;
    tmp->minutes = minutes;
    strcpy(tmp->command, command);
    tmp->info = info;
    first = tmp;
    first->next = first;
    // first = (task*)malloc(sizeof(task));
    // first->hours = hours;
    // first->minutes = minutes;
    // strcpy(first->command, command);
    // first->info = info;
    // first->next = first;

    return first;
}

task* Add(task* first, int hours, int minutes, char* command, int info)
{   
    if(first == NULL)
    {
        first = AddToEmpty(first, hours, minutes, command, info);
    }
    else
    {
        task *tmp, *p;
        p = first;
        while(p->next->hours < hours)
        {
            if(p->next == first)
                break;
            p = p->next;
        }
        
        if(p->next->hours == hours)
        {
            while(p->next->minutes < minutes)
            {
                if(p->next == first)
                    break;
                p = p->next;
            }

        }
        
        tmp = (task*)malloc(sizeof(task));
        tmp->hours = hours;
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
    timeinfo->tm_hour = task->hours;
    timeinfo->tm_min = task->minutes;
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
            if(tmp->hours < first->hours)
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
    return first;

}