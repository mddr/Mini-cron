#include "headers/task.h"
#include <stdio.h>

task* AddToEmpty(task* first, int hours, int minutes, char* command, int info)
{    
    task* tmp = (task*)malloc(sizeof(task));
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

    
    return first;
}