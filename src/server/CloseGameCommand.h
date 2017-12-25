//
// Created by shimon on 12/21/17.
//

#ifndef ADVANCEDPROGRAMMING1_CLOSEGAMECOMMAND_H
#define ADVANCEDPROGRAMMING1_CLOSEGAMECOMMAND_H

#include "Command.h"

class CloseGameCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, Game* game, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_CLOSEGAMECOMMAND_H
