#include "headers/demonize.h"
#include "headers/log.h"

void Demonize(char* programName)
{
    pid_t pid, sid;
    pid = fork();
    if (pid < 0)
    {
        LogError(programName, "Error forking a process.");   
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
        LogError(programName, "Error creating new session.");
        exit(EXIT_FAILURE);
    }
}

void ExecuteCommand(char* programName, char* command, char** arguments)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        LogError(programName, "Error forking a process.");   
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        //child created, return from parent
        return;
    }
    LogMessage(programName, "Executing command.");
    execvp(command, arguments);
}