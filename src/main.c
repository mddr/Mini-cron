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
        
    // Demonize(argv[0]);

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

        int i;
        char **commands = malloc(10*sizeof(char*));
        for(i=0;i<10;i++)
            commands[i] = malloc(64*sizeof(char));

        int isPipe = 0;
        //check if there are pipes
        commands[0] = strtok_r(tmp->command, "|", &commands[1]);
        i = 2;
        if (strlen(commands[1]) != 0) {
            strtok(commands[1], "|");
            isPipe = 1;
        }
        while (i < 10 && strlen(&command[i-1]) != 0)
        {
            commands[i] = strtok(NULL, "|");
            i++;
        }


        if (!isPipe)   //no pipes
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                LogError(argv[0], "Error forking a process.");   
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                ExecuteCommand(argv[0], tmp->command, tmp->info, outfile, 1);
            } 
        }
        else
        {
            int fd[2];
            int fd_in = 0;
            pid_t childpid;
            i = 0;
            while (commands[i] != NULL)
            {
                pipe(fd);
                childpid = fork();
                if (childpid < 0)
                {
                    LogError(argv[0], "Error forking a process.");   
                    exit(EXIT_FAILURE);
                }
                else if (childpid == 0)
                {
                    dup2(fd_in, 0);
                    close(fd[0]);
                    if (commands[i+1] != NULL) {
                        dup2(fd[1], 1);
                        ExecuteCommand(argv[0], commands[i], tmp->info, outfile, 0); //execute command
                    } else                    
                        ExecuteCommand(argv[0], commands[i], tmp->info, outfile, 1); //execute command
                    exit(EXIT_FAILURE);
                }
                else
                {
                    wait(NULL);
                    close(fd[1]);
                    fd_in = fd[0];
                    i++;
                }

            }
        }
        //go to the next task
        tmp = tmp->next;
    } while (tmp != tasks);
    
    // while(1)
    // {
    //     sleep(3);
    // }
    exit(EXIT_SUCCESS);
}