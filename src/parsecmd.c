//
// Created by david on 9/28/16.
//

#include "parsecmd.h"
#include <string.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "dircmds.h"
#include "history.h"


struct ProcessNode * activePid = NULL;
struct ProcessNode * lastActivePid = NULL;

int parseCommandLine(char **tokens, int count, int bg) {
    if (count < 1) return 0;

    char * output = malloc(sizeof(char *));
    int std_out = dup(1);
    int position = count;


    if (findRedirect(tokens, count, output, &position))
    {
        close(1);
        int opened = open(output, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        if (opened < 0)
        {
            //error opening descriptor
            close(1);
            dup(std_out);
            close(std_out);
            return 1;
        }
    }


    // check for built-in command
    int status;

    if (strcmp("exit", tokens[0]) == 0)     status = 255; // exit command quits the shell

    else if (strcmp("history", tokens[0]) == 0)  status = history(tokens, count); // standard history command

    else if (tokens[0][0] == '!') status = historyEntry(tokens); // single history entry with !

    else if (strcmp("pwd", tokens[0]) == 0) status = pwd();

    else if (strcmp("cd", tokens[0]) == 0) status = cd(tokens, count);

    else if (strcmp("jobs", tokens[0]) == 0) status = jobs();

    else status = otherProcess(tokens, position, bg);

    // restore stdout
    close(1);
    dup(std_out);
    close(std_out);

    return status;

}

int jobs() {
    struct ProcessNode * node = activePid;
    printf("Background processes: \n");
    while (node != NULL)
    {
        printf("\t%d\n", node->pid);
        node = node->next;
    }
    return 0;
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
            // not in background, wait before returning
            waitpid(child_pid, NULL, 0);
        }
        else
        {
            // add command to pid list
            struct ProcessNode *currentNode = malloc(sizeof(struct ProcessNode));
            if (activePid == NULL) {
                activePid = currentNode;
            } else{
                lastActivePid->next = currentNode;
            }
            currentNode->pid   = child_pid;
            currentNode->next = NULL;
            lastActivePid = currentNode;
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

int findRedirect(char **tokens, int count, char *output, int *position) {
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(tokens[i], ">") == 0)
        {
//            Found redirect string
            if ((i+1) < count) {
                free(output);
                output = malloc(sizeof(char) * strlen(tokens[i + 1]));
                strcpy(output, tokens[i + 1]);
                (*position) = i;
                return 1;
            }
        }
    }

    return 0;
}
