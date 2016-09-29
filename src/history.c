//
// Created by david on 9/26/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"

struct Node *tail;

int initHistory() {
    tail = NULL;
    // possibly load the history from a persistence file
    return 0;
}

int addCmd(char **cmd, int length) {
    struct Node* newNode = malloc(sizeof(struct Node));

    newNode->prev = tail;
    if (newNode->prev != NULL) {
        newNode->seq = newNode->prev->seq + 1;
    }
    else{
        newNode->seq = 1;
    }
    newNode->cmd_length = length;
    newNode->cmd = malloc(length * sizeof(char *));
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%d",i);
        newNode->cmd[i] = malloc(sizeof(char*));
        strcpy(newNode->cmd[i], cmd[i]);
    }
    tail = newNode;

    return 0;
}

/**
 * Print the command history
 *
 * @param length Number of history entries to print
 * @return Status code: 0 if all fine, 1 if all fine but exited before reaching length, 2 if other error
 */
int printHistory(int length) {
    int dist;
    struct Node* current = tail;
    for(dist = 0; dist < length; dist++) {
        if (current != NULL) {
            printf("%d: ", current->seq);

            int j;
            for (j = 0; j < current->cmd_length; j++)
            {
                printf("%s ", current->cmd[j]);
            }
            printf("\n");
            current = current->prev;
        }
        else
            return 1;
    }

    return 0;
}

int exitHistory() {
    // possibly save the history to some persistence file
    // todo: free the command history memory
    struct Node* current = tail;
    while (current != NULL)
    {
        int i;
        for (i = 0; i < current->cmd_length; i++)
        {
            free(current->cmd[i]);
        }
        free(current->cmd);
        struct Node* temp = current;
        current = current->prev;
        free(temp);
    }
    tail = current;
    return 0;
}

int printEntry(int index) {
    struct Node* current = tail;

    if (index > current->seq)
        printf("no command found in history\n");

    else
        while (current != NULL)
        {
            if (current->seq == index)
            {
                printf("%d: ", current->seq);
                int j;
                for (j = 0; j < current->cmd_length; j++)
                {
                    printf("%s ", current->cmd[j]);
                }
                printf("\n");
                return 0;
            }
            current = current->prev;
        }
    return 1;
}
