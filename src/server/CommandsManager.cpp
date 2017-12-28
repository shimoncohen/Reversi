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
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}

void CommandsManager::executeCommand(string command, vector<string> args, vector<Game*> &games,
                                     vector<pthread_t*> &threadVector, int client) {
    Command *commandObj = commandsMap[command];
    try {
        commandObj->execute(args, games, threadVector, client);
    } catch (const char* msg) {
        throw msg;
    }
}