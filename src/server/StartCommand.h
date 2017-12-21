// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_STARTCOMMAND_H
#define ADVANCEDPROGRAMMING1_STARTCOMMAND_H

#include "Command.h"
#define STARTMESSAGE "Start"

class StartCommand : public Command {
    void execute(vector<string> args, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_STARTCOMMAND_H
