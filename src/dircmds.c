//
// Created by david on 9/28/16.
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <malloc.h>
#include "dircmds.h"

#define MAX_DIRECTORY_LENGTH 200
int pwd() {
    char dir[MAX_DIRECTORY_LENGTH];

    if (getcwd(dir, MAX_DIRECTORY_LENGTH) == NULL)
        return 1;
    printf("%s\n", dir);
    return 0;
}

int cd(char **tokens, int count) {
    char destCat[MAX_DIRECTORY_LENGTH] = "\0";
    int return_val = 0;
    if (count < 2) // eventually return to home dir
    {
        struct passwd *pw;
        uid_t uid;
        uid = geteuid ();
        pw = getpwuid (uid);
        if (pw)
        {
            char * basePath = "/home/";
            memcpy(destCat, basePath, strlen(basePath));
            strcat(destCat, pw->pw_name);
            strcat(destCat, "/");
            free(basePath);
        } else {
            return_val = 1;
        }
    } else {
        char *dest = tokens[1];

        if (dest[0] == '/') // absolute path
        {

        } else {
            getcwd(destCat, MAX_DIRECTORY_LENGTH);
            strcat(destCat, "/");
        }

        strcat(destCat, dest);
    }
    return_val |= chdir(destCat);
//    free(destCat);

    return return_val;
}
