#include "headers/read.h"
#include "headers/log.h"

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

    int taskfile = GetFile(argv[1], O_RDONLY);
    int outfile = GetFile(argv[2], O_WRONLY);

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
    
    // while(1)
    // {
    //     sleep(3);
    // }

    exit(EXIT_SUCCESS);
}