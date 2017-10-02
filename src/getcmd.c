//
// Created by david on 9/26/17.
//

#include "getcmd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
// This code is given for illustration purposes. You need not include or follow this
// strictly. Feel free to write better or bug free code. This example code block does not
// worry about deallocating memory. You need to ensure memory is allocated and deallocated
// properly so that your shell works without leaking memory.
//
int getcmd(char *prompt, char *args[], int *background)
{
    int i = 0;
    __ssize_t length;
    char *token, *loc;
    char *line = NULL;
    size_t linecap = 0;
    printf("%s", prompt);
    length = getline(&line, &linecap, stdin);
    if (length <= 0) {
        exit(-1);
    }
// Check if background is specified..
    if ((loc = index(line, '&')) != NULL) {
        *background = 1;
        *loc = ' ';
    } else
        *background = 0;
    while ((token = strsep(&line, " \t\n")) != NULL) {
        int j;
        for (j = 0; j < strlen(token); j++)
            if (token[j] <= 32)
                token[j] = '\0';
        if (strlen(token) > 0)
            args[i++] = token;
    }

    free(line);
    return i;
}
