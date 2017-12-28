//
// Created by shimon on 12/21/17.
//

#ifndef ADVANCEDPROGRAMMING1_CLOSEGAMECOMMAND_H
#define ADVANCEDPROGRAMMING1_CLOSEGAMECOMMAND_H

#include "Command.h"

#define CLOSE "close"
#define CLOSESIZE 8

class CloseGameCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &game, /*vector<pthread_t*> &threadVector,*/ int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_CLOSEGAMECOMMAND_H
