//
// Created by david on 9/26/16.
//

#ifndef DASH_HISTORY_H
#define DASH_HISTORY_H

struct HistoryNode {
    int seq;
    int cmd_length;
    char** cmd;
    struct HistoryNode* prev;
};


int initHistory();
int addCmd(char **cmd, int length);
int printHistory(int length);
int printEntry(int index);
int exitHistory();
int history(char ** token, int cnt);
int historyEntry(char ** token);
#endif //DASH_HISTORY_H
