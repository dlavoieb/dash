#include "getcmd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"

int main(void)
{
    char *args[20];
    int bg;
    initHistory();
    while(1) {
        bg = 0;
        int cnt = getcmd(">>", args, &bg);
        if (cnt < 1) continue;

        if (strcmp("exit", args[0]) == 0) break; // check for the exit command
        if (strcmp("history", args[0]) == 0) {
            // check for the history command
            int depth = (int) strtol(args[1], NULL, 10);
            if (depth == 0) depth = 10;
            printHistory(depth);
        }

        addCmd(args, cnt);

        /* the steps can be..:
         * (1) fork a child process using fork()
         * (2) the child process will invoke execvp()
         * (3) if background is not specified, the parent will wait,
         * otherwise parent starts the next command...
         */

    }
    exitHistory();
    exit(0);
}