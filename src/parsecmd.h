//
// Created by david on 9/28/17.
//

#ifndef DASH_PARSECMD_H
#define DASH_PARSECMD_H

#include <zconf.h>

struct ProcessNode
{
    pid_t pid;
    struct ProcessNode * next;
    struct ProcessNode * previous;
};

int parseCommandLine(char ** tokens, int count, int bg);

int otherProcess(char ** tokens, int count, int bg);

int jobs();

int fg(char **tokens, int count);

int findRedirect(char **tokens, int count, char *output, int *position, int *append);

void free_nodes();

int stop_active_process();


#endif //DASH_PARSECMD_H
