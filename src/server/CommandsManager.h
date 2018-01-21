// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_COMMANDSMANAGER_H
#define ADVANCEDPROGRAMMING1_COMMANDSMANAGER_H

#include <vector>
#include <map>
#include "iostream"
#include "Command.h"
#include "StartCommand.h"
#include "MakeMoveCommand.h"
#include "JoinGameCommand.h"
#include "GetGameListCommand.h"
#include "CloseGameCommand.h"
using namespace std;

/*
 * Command manager gives a commands execute function by given label.
 * Holds a map of executes by label.
 */
class CommandsManager {
public:
    /*
	 * function name: CommandsManager.
	 * input: none.
	 * output: none.
     * operation: constructor.
    */
    CommandsManager();
    /*
	 * function name: ~CommandsManager.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    ~CommandsManager();
    /*
	 * function name: executeCommand.
	 * input: vector of string, a vector of all the games in the server, a vector
     * of all the threads running currently, the number of client's socket.
	 * output: none.
     * operation: creates the desired command and executes the command according to its type.
    */
    void executeCommand(string command, vector <string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                        pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, ThreadPool& pool, int client = 0);
private:
    map<string, Command *> commandsMap;
};

#endif //ADVANCEDPROGRAMMING1_COMMANDSMANAGER_H