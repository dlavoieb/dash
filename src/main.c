
#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "parsecmd.h"
#include "getcmd.h"

int main(void)
{
    char *args[20];
    int bg;
    initHistory();
    while(1) {
        bg = 0;
        int cnt = getcmd(">>", args, &bg);
        addCmd(args, cnt);
        int ret = parseCommandLine(args, cnt, bg);

        if (ret == 0)
            // all good status
            continue;

        else if (ret == 1)
        {
            printf("last exit unclean\n");
            // error in the last command
            continue;
        }
        else if (ret == 255)
            // exit code
            break;
    }
    exitHistory();
    exit(0);
}