//
// Created by david on 9/28/17.
//

#include "parsecmd.h"
#include <string.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "dircmds.h"

static struct ProcessNode * activePid = NULL;
static struct ProcessNode * lastActivePid = NULL;
pid_t runningProcess = 0;

void free_node_impl(struct ProcessNode* node);

int parseCommandLine(char **tokens, int count, int bg) {
    if (count < 1) return 0;

    char * output = malloc(sizeof(char *));
    int std_out = dup(1);
    int position = count;
    int append = 0;


    if (findRedirect(tokens, count, output, &position, &append))
    {
        int file_flags = append ? O_WRONLY | O_APPEND | O_CREAT : O_WRONLY | O_CREAT | O_TRUNC;
        close(1);
        int opened = open(output, file_flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
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

    if (strcmp("exit", tokens[0]) == 0) status = 255; // exit command quits the shell

    else if (strcmp("pwd", tokens[0]) == 0) status = pwd();

    else if (strcmp("cd", tokens[0]) == 0) status = cd(tokens, count);

    else if (strcmp("jobs", tokens[0]) == 0) status = jobs();

    else if (strcmp("fg", tokens[0]) == 0) status = fg(tokens, count);

    else status = otherProcess(tokens, position, bg);

    // restore stdout
    close(1);
    dup(std_out);
    close(std_out);

    free(output);
    return status;

}

int fg(char **tokens, int count) {
    int index = 0;
    struct ProcessNode* node = activePid;
    if (count > 1) index = (int) strtol(tokens[1], NULL, 10);
    if (count == 1 || index == 0) node = lastActivePid;
    else{
        int i;
        for (i = 0; i < index; i++)
        {
            if (node != NULL)
                node = node->next;
        }

    }

    if (node != NULL)
    {
        pid_t pid = node->pid;
        if (node->previous != NULL)
        {
            (node->previous)->next = node->next;
        }
        free(node);
        waitpid(pid, NULL, 0);
    }


    return 0;
}

int jobs() {
    struct ProcessNode * node = activePid;
    printf("Background processes: \n");
    while (node != NULL)
    {
        // check if current node still active
        int status;
        waitpid(node->pid, &status, WNOHANG);
        if (WIFEXITED(status) || WIFSTOPPED(status))
        {
            if (node->previous!=NULL) {
                (node->previous)->next = node->next;

            }
            if (node->next != NULL) {
                (node->next)->previous = node->previous;
            }

            free(node);
        }
        else
        {
            printf("\t%d\n", node->pid);
        }
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
            runningProcess = child_pid;
            waitpid(child_pid, NULL, 0);
            runningProcess = 0;
//            printf("Child process has finished\n");
        }
        else
        {
            // add command to pid list
            struct ProcessNode *currentNode = malloc(sizeof(struct ProcessNode));
            if (activePid == NULL)
            {
                activePid = currentNode;
            }
            else
            {
                lastActivePid->next = currentNode;
            }
            currentNode->pid  = child_pid;
            currentNode->next = NULL;
            currentNode->previous = lastActivePid;
            lastActivePid = currentNode;

//            free(currentNode);
        }
    }

    else
    {
        // child process
        unsigned int w,rem;
        w = (unsigned int) (rand() % 10);
        rem=sleep(w);
        //handles interruption by signal
        while(rem!=0)
        {
            rem=sleep(rem);
        }

        execvp(tokens[0], tokens);
        perror("exec command failed");
        exit(1);
    }


    return 0;
}

int findRedirect(char **tokens, int count, char *output, int *position, int *append) {
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0)
        {
            (*append) = strcmp(tokens[i], ">>") == 0; // determine if should append or override file
//            Found redirect string
//            Put output file name in pointer
            if ((i+1) < count) {
                strcpy(output, tokens[i + 1]);
                (*position) = i;
                return 1;
            }
        }
    }

    return 0;
}

void free_nodes()
{
    if (activePid != NULL)
        free_node_impl(activePid);
}

void free_node_impl(struct ProcessNode* node)
{
    if (node->next != NULL)
    {
        free_node_impl(node->next);
    } else {
        free(node);
    }
}

int stop_active_process()
{
    if (runningProcess != 0)
    {
        return kill(runningProcess, SIGINT);

    }
    return -1;
}