//
// Created by david on 9/26/16.
//

#ifndef DASH_HISTORY_H
#define DASH_HISTORY_H

struct Node {
    int seq;
    int cmd_length;
    char** cmd;
    struct Node* prev;
};


int initHistory();
int addCmd(char **cmd, int length);
int printHistory(int length);
int exitHistory();
#endif //DASH_HISTORY_H
