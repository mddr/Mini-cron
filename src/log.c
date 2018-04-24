#include "headers/log.h"

void LogError(char* programName, char* message)
{
    openlog(programName, LOG_PID | LOG_NDELAY, LOG_DAEMON);    
    syslog(LOG_ERR, "%s", message);
    closelog();    
}

void LogMessage(char* programName, char* message)
{
    openlog(programName, LOG_PID | LOG_NDELAY, LOG_DAEMON);    
    syslog(LOG_INFO, "%s", message);
    closelog();    
}