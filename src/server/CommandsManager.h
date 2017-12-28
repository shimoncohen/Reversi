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

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command, vector <string> args, vector<Game*> &games, /*vector<pthread_t*> &threadVector,*/
                        int client = 0);
private:
    map<string, Command *> commandsMap;
};

#endif //ADVANCEDPROGRAMMING1_COMMANDSMANAGER_H