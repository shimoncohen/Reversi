// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H
#define ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H

#include "Command.h"
#include "Handler.h"
#define STARTMESSAGE "Start"
#define STARTMESSAGESIZE 6
#define NOTEXIST "NotExist"
#define NOTEXISTSIZE 9
#define FIRST 1
#define SECOND 2

class joinGameCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H
