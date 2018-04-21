#include "headers/task.h"

void Push(task* head, int hours, int minutes, char* command, int info)
{
    task * current = head;
    while(current->next->hours < hours)
    {
        current = current->next;
    }
    if(current->next->hours == hours)
    {
        while(current->next->minutes < minutes)
        {
            current = current->next;
        }
    }
    task * tmp = current->next;
    current->next = malloc(sizeof(task));
    current->next->next = tmp;
    current->next->hours = hours;
    current->next->minutes = minutes;
    strcpy(current->next->command, command);
    current->next-> info = info;
}