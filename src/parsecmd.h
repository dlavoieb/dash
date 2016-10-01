//
// Created by david on 9/28/16.
//

#ifndef DASH_PARSECMD_H
#define DASH_PARSECMD_H

#include <zconf.h>

struct ProcessNode
{
    pid_t pid;
    struct ProcessNode * next;
};

struct ProcessNode * activePid;

int parseCommandLine(char ** tokens, int count, int bg);

int otherProcess(char ** tokens, int count, int bg);

#endif //DASH_PARSECMD_H
