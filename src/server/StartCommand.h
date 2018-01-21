// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_STARTCOMMAND_H
#define ADVANCEDPROGRAMMING1_STARTCOMMAND_H

#include "Command.h"

#define EXISTS "AlreadyExist"
#define EXISTSIZE 15
#define DOSENTEXIST "DosentExist"
#define DOSENTEXISTSIZE 13

/*
 * Command in charge of creating a new game and adding it to the games list
 */
class StartCommand : public Command {
public:
    void execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                 pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, ThreadPool& pool, int client = 0);
};


#endif //ADVANCEDPROGRAMMING1_STARTCOMMAND_H
