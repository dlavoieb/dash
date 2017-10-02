
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "parsecmd.h"
#include "getcmd.h"


static void sigint_handler (int signal)
{
    // forward signal to running process
//    printf("\b\bSIGINT\n");
    stop_active_process();
}

static void sigtstp_handler (int signal)
{
//printf("\b\bHA! This signal is ignored, sucker! \n");
}

int main(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    time_t now;
    srand((unsigned int) (time(&now)));

    char *args[20];
    int bg;
    while(1) {
        bg = 0;
        int cnt = getcmd(">> ", args, &bg);
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

    free_nodes();
    exit(0);
}