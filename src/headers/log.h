#ifndef LOG_H
#define LOG_H

#include <syslog.h>

void LogError(char*, char*);
void LogMessage(char*, char*);

#endif