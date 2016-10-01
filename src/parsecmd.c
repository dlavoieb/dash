//
// Created by david on 9/28/16.
//

#include "parsecmd.h"
#include <string.h>
#include <zconf.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "dircmds.h"
#include "history.h"

int parseCommandLine(char **tokens, int count, int bg) {
    if (count < 1) return 0;
    
    // check for built-in command


    if (strcmp("exit", tokens[0]) == 0)     return 255; // exit command quits the shell

    if (strcmp("history", tokens[0]) == 0)  return history(tokens, count); // standard history command

    if (tokens[0][0] == '!') return historyEntry(tokens); // single history entry with !

    if (strcmp("pwd", tokens[0]) == 0) return pwd();

    if (strcmp("cd", tokens[0]) == 0) return cd(tokens, count);

    return otherProcess(tokens, count, bg);

}

int otherProcess(char **tokens, int count, int bg) {

    tokens[count] = NULL;

    pid_t child_pid;
    child_pid = fork();
    if (child_pid)
    {
        // parent process
        if (bg == 0)
        {
            // not in background, redirect output and wait before returning
            waitpid(child_pid, NULL, 0);
        }
        else
        {
        }
    }

    else
    {
        // child process
        execvp(tokens[0], tokens);
        perror("exec command failed");
        exit(1);
    }


    return 0;
}
