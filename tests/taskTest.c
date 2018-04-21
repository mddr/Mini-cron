#include "../src/headers/task.h"
#include <stdio.h>

// void Push(task * head, int hours, int minutes, char* command, int info)
int push_on_empty_list_should_create_new()
{
    task* firstNode = NULL;
    Push(firstNode, 12, 15, "ls", 0);

    return firstNode == NULL;     
}

int provided_later_hour_and_minute_should_add_task_add_the_end()
{
    task* firstNode = malloc(sizeof(task));
    firstNode->hours = 10;
    firstNode->minutes = 10;
    strcpy(firstNode->command, "pwd");
    firstNode->info = 1;
    firstNode->next = firstNode;

    Push(firstNode, 12, 15, "ls", 0);

    return firstNode->next != firstNode && firstNode->next->hours == 12; 
}

int main()
{
    printf("%s: %d\n", "push_on_empty_list_should_create_new(): ", push_on_empty_list_should_create_new());
    printf("%s: %d\n", "provided_later_hour_and_minute_should_add_task_add_the_end: ", 
                        push_on_empty_list_should_create_new());
}

