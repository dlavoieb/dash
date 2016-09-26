#include "getcmd.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    char *args[20];
    int bg;
    while(1) {
        bg = 0;
        int cnt = getcmd(">>", args, &bg);

        if (args[0] == NULL) continue;
        if (strcmp("exit", args[0]) == 0) exit(0); // check for the exit command
        printf("cnt=%d\n", cnt);

        /* the steps can be..:
        (1) fork a child process using fork()
        (2) the child process will invoke execvp()
        (3) if background is not specified, the parent will wait,
        otherwise parent starts the next command... */

    }
}