#include "headers/read.h"
#include "headers/log.h"
#include "headers/task.h"
#include "headers/print.h"

int main(int argc, char* argv[]) 
{
    if(argc != 3) 
    {
        LogError(argv[0], "Invalid arguments.");
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
        exit(EXIT_FAILURE);
    }
    else if (outfile == -1) 
    {
        LogError(argv[0], "Invalid outfile.");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    int counter = read(taskfile, buffer, sizeof(buffer));
    int i;
    for (i=0;i<counter;++i)
        printf("%c", buffer[i]);
        
    // while(1)
    // {
    //     sleep(3);
    // }
    PrintUsage();
    exit(EXIT_SUCCESS);
}