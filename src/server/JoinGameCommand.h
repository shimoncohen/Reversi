// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H
#define ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H

#include "Command.h"
#define STARTMESSAGE "Start"

class joinGameCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> games, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H
