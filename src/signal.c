#include <signal.h>
#include "headers/signal.h"
#include "headers/log.h"
#include "headers/task.h"
#include "headers/print.h"
#include "headers/demonize.h"
#include "headers/signal.h"
#include "headers/global.h"

char* infile;
char* ofile;
task* tasks;
task* tmp;

void SIGUSR1Signal(int sig)
{
    if(sig == SIGUSR1)
    {
        char* filename = "./minicron.o";
        char** cmd = {&filename, infile, ofile, NULL};
        execvp(filename,cmd);
    }
}

void SIGUSR2Signal(int sig)
{
    if(sig == SIGUSR2)
    {
        task *old = tmp;
        while(old != tasks)
        {
            LogMessage("./minicron.o", old->command);
            old = old->next;
        }
        
        int seconds = SleepTime(tmp);
        if (seconds < 0)
            seconds += 86400;
        sleep(SleepTime(tmp));
    }
}

void SIGINTSignal(int sig)
{
    if(sig == SIGINT)
    {
        exit(EXIT_SUCCESS);
    }
}