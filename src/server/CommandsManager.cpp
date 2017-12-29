// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "CommandsManager.h"

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new GetGameListCommand();
    commandsMap["join"] = new joinGameCommand();
    commandsMap["play"] = new MakeMoveCommand();
    commandsMap["close"] = new CloseGameCommand();
}

CommandsManager::~CommandsManager() {
    // creating an iterator to go over the map
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        // deleting the map
        delete it->second;
    }
}

void CommandsManager::executeCommand(string command, vector<string> args, vector<Game*> &games,
                                     vector<pthread_t*> &threadVector, int client) {
    // creating the command
    Command *commandObj = commandsMap[command];
    try {
        // executing the command
        commandObj->execute(args, games, threadVector, client);
    } catch (const char* msg) {
        throw msg;
    }
}