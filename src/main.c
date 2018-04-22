#include "headers/read.h"
#include "headers/log.h"
#include "headers/task.h"
#include "headers/print.h"

int main(int argc, char* argv[]) 
{
    if(argc != 3) 
    {
        LogError(argv[0], "Invalid arguments.");
        PrintUsage();
        exit(EXIT_FAILURE);
    }
        
    pid_t pid, sid;
    pid = fork();
    if (pid < 0)
    {
        LogError(argv[0], "Error forking a process.");   
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        //child created
        exit(EXIT_SUCCESS);
    }

    sid = setsid();
    if(sid < 0)
    {
        LogError(argv[0], "Error creating new session.");
        exit(EXIT_FAILURE);
    }

    int taskfile = open(argv[1], O_RDONLY);
    int outfile = open(argv[2], O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

    if (taskfile == -1) 
    {
        LogError(argv[0], "Invalid taskfile.");
        PrintUsage();    
        exit(EXIT_FAILURE);
    }
    else if (outfile == -1) 
    {
        LogError(argv[0], "Invalid outfile.");
        PrintUsage();
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    read(taskfile, buffer, sizeof(buffer));

    task* tasks = malloc(sizeof(task));
    tasks->next = tasks;

    int hours, minutes, info;
    char *command;
    char *delimeter = ":\n";
    char *line = strtok(buffer, delimeter);

    while (line != NULL)
    {
        hours = atoi(line);
        minutes = atoi(strtok(NULL, delimeter));
        command = strtok(NULL, delimeter);
        info = atoi(strtok(NULL, delimeter));
        line = strtok(NULL, delimeter);
        if (tasks->next == tasks) 
        {
            // tasks->hours = hours;
            // tasks->minutes = minutes;
            // strcpy(tasks->command, command);
            // tasks->info = info;
            tasks = AddToEmpty(tasks,hours,minutes,command,info);
        } else {
            // printf("%d %d %s %d\n", hours, minutes, command, info);
            tasks = Add(tasks, hours, minutes, command, info);

        }
        
    }
    // printf("%d %d %s %d\n", tasks->hours, tasks->minutes, tasks->command, tasks->info);
// int i;
//     for(i = 0;i<2;i++) {
        printf("%d %d %s %d\n", tasks->hours, tasks->minutes, tasks->command, tasks->info);
        // tasks = tasks->next;
    // }
        printf("%d %d %s %d\n", tasks->next->hours, tasks->next->minutes, tasks->next->command, tasks->next->info);
    
    // while(1)
    // {
    //     sleep(3);
    // }
    exit(EXIT_SUCCESS);
}