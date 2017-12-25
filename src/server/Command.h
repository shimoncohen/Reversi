// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_COMMAND_H
#define ADVANCEDPROGRAMMING1_COMMAND_H

#include <vector>
#include "iostream"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Game.h"

using namespace std;

class Command {
public:
    virtual void execute(vector<string> args, vector<Game*> &games, Game* game, int client = 0) = 0;
    virtual ~Command() {}
};

#endif //ADVANCEDPROGRAMMING1_COMMAND_H
