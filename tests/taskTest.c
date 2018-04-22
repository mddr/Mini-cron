#include "../src/headers/task.h"
#include <stdio.h>

char* add_on_empty_list_should_create_new()
{
    task* firstNode = NULL;
    firstNode = Add(firstNode, 12, 15, "ls", 0);

    return firstNode != NULL ? "pass" : "fail";     
}

char* provided_later_hour_and_minute_should_add_task_add_the_end()
{
    task* firstNode = malloc(sizeof(task));
    firstNode->hours = 10;
    firstNode->minutes = 10;
    strcpy(firstNode->command, "pwd");
    firstNode->info = 1;
    firstNode->next = firstNode;

    firstNode = Add(firstNode, 12, 15, "ls", 0);

    return (firstNode->next != firstNode && firstNode->next->hours == 12 )? "pass" : "fail"; 
}

int main()
{
    printf("%s: %s\n", "add_on_empty_list_should_create_new()", add_on_empty_list_should_create_new());
    printf("%s: %s\n", "provided_later_hour_and_minute_should_add_task_add_the_end", 
                        provided_later_hour_and_minute_should_add_task_add_the_end());
}

