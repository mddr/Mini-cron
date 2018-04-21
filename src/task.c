#include "headers/task.h"

<<<<<<< HEAD
task* AddToEmpty(task* first, int hours, int minutes, char* command, int info)
=======
void Push(task* head, int hours, int minutes, char* command, int info)
>>>>>>> fc95d86adeb3efc0edb82ccbe0452068ff00e569
{
    task* tmp = (task*)malloc(sizeof(task));
    tmp->hours = hours;
    tmp->minutes = minutes;
    strcpy(tmp->command, command);
    tmp->info = info;
    first = tmp;
    first->next = first;
    return first;
}

task* Add(task* first, int hours, int minutes, char* command, int info)
{
    if(first == NULL)
    {
        AddToEmpty(first, hours, minutes, command, info);
    }
    task *tmp, *p;
    p = first;
    while(p->next->hours < hours)
    {
        if(p->next == first);
            break;
        p = p->next;
    }
    if(p->next->hours == hours)
    {
        while(p->next->minutes < minutes)
        {
            if(p->next == first);
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