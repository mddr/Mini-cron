#include "headers/log.h"
#include "headers/task.h"
#include "headers/print.h"
#include "headers/demonize.h"
#include "headers/signal.h"
#include <signal.h>
#include <unistd.h>

char* infile;
char* ofile;
task* tasks;
task* tmp;

void clear()
{
    while(getchar() != '\n');
}


int main(int argc, char* argv[]) 
{   
    signal(SIGUSR1, SIGUSR1Signal);
    signal(SIGUSR2, SIGUSR2Signal);
    signal(SIGINT, SIGINTSignal);
    
    if(argc != 3) 
    {
        LogError(argv[0], "Invalid arguments.");
        PrintUsage();
        exit(EXIT_FAILURE);
    }

    Demonize(argv[0]);
    infile = argv[1];
    ofile = argv[2];
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

    tasks = NULL;
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
    
    tasks = KindOfSort(tasks);
    tmp = tasks;
    
    while(1)
    // do
    {
        int seconds = SleepTime(tmp);

        while (seconds < 0) 
        {
            tmp = tmp->next;
            seconds = SleepTime(tmp);
            if (tmp == tasks)
            {
                seconds += 86400;
                break;
            }
        }

        printf("%d\n", seconds);
        LogMessage(argv[0], "Daemon goes to sleep");
        sleep(seconds);

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
            int isLast = 0;
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
                        isLast = 0;
                    } else {
                        isLast = 1;
                    }
                    ExecuteCommand(argv[0], commands[i], tmp->info, outfile, isLast);
                    exit(EXIT_FAILURE);
                }
                else
                {  
                    int status;
                    wait(&status);
                    close(fd[1]);
                    
                    char snum[32];
                    sprintf(snum, "%d", status);
                    strcat(snum, " - process exit code.");
                    LogMessage(argv[0],snum);
                    fd_in = fd[0];
                    i++;
                }

            }
        }
        //go to the next task
        sleep(1);
        tmp = tmp->next;
    } 
    
    exit(EXIT_SUCCESS);
}