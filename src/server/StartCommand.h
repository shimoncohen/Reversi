// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_STARTCOMMAND_H
#define ADVANCEDPROGRAMMING1_STARTCOMMAND_H

#include "Command.h"

class StartCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> games, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_STARTCOMMAND_H
