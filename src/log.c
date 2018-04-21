#include "headers/log.h"

void LogError(char* programName, char* message)
{
    openlog(programName, LOG_PID | LOG_NDELAY, 0);
    syslog(LOG_ERR, "%s", message);
    closelog();
}