#include "headers/log.h"
#include "headers/task.h"
#include "headers/print.h"
#include "headers/demonize.h"

int main(int argc, char* argv[]) 
{
    if(argc != 3) 
    {
        LogError(argv[0], "Invalid arguments.");
        PrintUsage();
        exit(EXIT_FAILURE);
    }
        
    Demonize(argv[0]);

    int taskfile = open(argv[1], O_RDONLY);
    int outfile = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

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

    task* tasks = NULL;
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
        tasks = Add(tasks, hours, minutes, command, info);
        
    }
    tasks=KindOfSort(tasks);
    task* tmp = tasks;
    
    do
    {
        // sleep(SleepTime(tmp));

        //split command and arguments
        char *savePtr;
        char *commandName = strtok_r(tmp->command, " ", &savePtr);

        //assumed maximum of 10 arguments, 64 chars each + NULL at the end
        char **arguments = malloc(10*sizeof(char*));
        int i;
        for (i=0;i<11;i++)
            arguments[i] = malloc(64*sizeof(char));
        i=2;
        arguments[0] = commandName;
        arguments[1] = strtok(savePtr, " ");
        while (i < 10 && arguments[i-1] != NULL)
        {
            arguments[i] = strtok(NULL, " ");
            i++;
        }
        switch(tmp->info)
        {
            case 0:
                dup2(outfile, STDOUT_FILENO);
                PrintCommandWithArguments(arguments);
                break;
            case 1:
                dup2(STDERR_FILENO, STDOUT_FILENO);
                break;
            case 2:
                dup2(STDERR_FILENO, STDOUT_FILENO);
                dup2(outfile, STDOUT_FILENO);
                break;
            default:
                LogError(argv[0], "Invalid info provided.");
                return -1;
        }

        arguments[i] = NULL;
        ExecuteCommand(argv[0], commandName, arguments);

        //go to the next task
        tmp = tmp->next;
    } while (tmp != tasks);
    
    // while(1)
    // {
    //     sleep(3);
    // }
    exit(EXIT_SUCCESS);
}