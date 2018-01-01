// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_COMMAND_H
#define ADVANCEDPROGRAMMING1_COMMAND_H

#include <vector>
#include "iostream"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Game.h"

using namespace std;

/*
 * General command interface.
 */
class Command {
public:
    /*
	 * function name: execute.
	 * input: vector of string, a vector of all the games in the server, a vector
     * of all the threads running currently, the number of client's socket and a mutex lock.
	 * output: none.
     * operation: executes the command according to its type.
    */
    virtual void execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                         pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, int client = 0) = 0;
    /*
	 * function name: ~Command.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    virtual ~Command() {}
};

#endif //ADVANCEDPROGRAMMING1_COMMAND_H
