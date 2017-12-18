// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_STARTCOMMAND_H
#define ADVANCEDPROGRAMMING1_STARTCOMMAND_H

#include "Command.h"

class StartCommand : public Command {
    void execute(vector<string> args);
};


#endif //ADVANCEDPROGRAMMING1_STARTCOMMAND_H
