// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H
#define ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H

#include "Command.h"
#include "Handler.h"
#define STARTMESSAGE "Start"
#define STARTMESSAGESIZE 10
#define NOTEXIST "NotExist"
#define NOTEXISTSIZE 10
#define FIRST 1
#define SECOND 2

/*
 * Command in charge of adding a second player to a waiting game and then run the new game
 */
class joinGameCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                 pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, ThreadPool& pool, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_JOINGAMECOMMAND_H
