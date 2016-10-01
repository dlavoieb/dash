//
// Created by david on 9/28/16.
//

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "dircmds.h"

int pwd() {
    char dir[200];

    if (getcwd(dir, 200) == NULL)
        return 1;
    printf("%s\n", dir);
    return 0;
}

int cd(char **tokens, int count) {
    if (count < 2) return 1; // eventually return to home dir

    char * dest = tokens[1];

    char destCat[250] = "\0";
    if (dest[0] == '/') // absolute path
    {

    }
    else
    {
        getcwd(destCat, 250);
        strcat(destCat, "/");
    }

    strcat(destCat, dest);

    return chdir(destCat);
}
