#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
    pid_t pid, sid;
    pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    //TODO: open logs
    
    if(argc != 3) 
    {
        //log failure
        exit(EXIT_FAILURE);
    }

    sid = setsid();
    if(sid < 0)
    {
        //log failure
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1)
    {
        sleep(30);
    }

    exit(EXIT_SUCCESS);
}