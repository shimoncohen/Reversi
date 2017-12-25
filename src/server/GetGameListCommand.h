//
// Created by shimon on 12/21/17.
//

#ifndef ADVANCEDPROGRAMMING1_GETGAMELISTCOMMAND_H
#define ADVANCEDPROGRAMMING1_GETGAMELISTCOMMAND_H

#include "Command.h"

#define NOGAMES "no available games\n"
#define NOGAMESIZE 19

class GetGameListCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_GETGAMELISTCOMMAND_H
