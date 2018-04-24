#include "headers/demonize.h"
#include "headers/log.h"
#include "headers/print.h"

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

void ExecuteCommand(char* programName, char* command, int info, int outfile, int isLastFlag)
{

    //split command and arguments
    char *saveArguments;
    char *commandName = strtok_r(command, " ", &saveArguments);

    //assumed maximum of 10 arguments, 64 chars each + NULL at the end
    int i;
    char **arguments = malloc(10*sizeof(char*));
    for (i=0;i<11;i++)
        arguments[i] = malloc(64*sizeof(char));
    i=2;
    arguments[0] = commandName;
    arguments[1] = strtok(saveArguments, " ");
    while (i < 10 && arguments[i-1] != NULL)
    {
        arguments[i] = strtok(NULL, " ");
        i++;
    }

    arguments[i] = NULL;

    if(isLastFlag) 
    {
        switch(info)
        {
            case 0:
                printf(" ");
                dup2(outfile, STDOUT_FILENO);
                break;
            case 1:
                printf(" ");
                dup2(STDERR_FILENO, STDOUT_FILENO);
                break;
            case 2:
                break;
            default:
                LogError(programName, "Invalid info provided.");
                return;
        }
        PrintCommandWithArguments(arguments);
        LogMessage(programName, "Executing command.");
    }
    execvp(commandName, arguments);
    exit(EXIT_FAILURE);
}