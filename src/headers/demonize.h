#ifndef DEMONIZE_H
#define DEMONIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void Demonize();
void RunPipedCommand(char* programName, char* pipedCommand, int info, int outfile);
void ExecuteCommand(char* programName, char* command, int info, int outfile);

#endif