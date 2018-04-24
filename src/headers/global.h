#ifndef GLOBAL_H
#define GLOBAL_H

#include <signal.h>
#include <unistd.h>
#include "task.h"

extern char* infile;
extern char* ofile;
task* tasks;
task* tmp; 

#endif