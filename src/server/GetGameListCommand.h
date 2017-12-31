// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_GETGAMELISTCOMMAND_H
#define ADVANCEDPROGRAMMING1_GETGAMELISTCOMMAND_H

#include "Command.h"

#define NOGAMES "no available games\n"
#define NOGAMESIZE 19

/*
 * Command in charge of sending a client the waiting games list
 */
class GetGameListCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector, int client = 0);
};

#endif //ADVANCEDPROGRAMMING1_GETGAMELISTCOMMAND_H
