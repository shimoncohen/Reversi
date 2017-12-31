// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_MAKEMOVECOMMAND_H
#define ADVANCEDPROGRAMMING1_MAKEMOVECOMMAND_H

#include "Command.h"
#include <cstring>
#define BUFFERSIZE 200

/*
 * Command in charge of sending a given move to the players opponent
 */
class MakeMoveCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_MAKEMOVECOMMAND_H
