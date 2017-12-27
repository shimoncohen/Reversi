//
// Created by shimon on 12/23/17.
//

#ifndef ADVANCEDPROGRAMMING1_HANDLER_H
#define ADVANCEDPROGRAMMING1_HANDLER_H

#include "CommandsManager.h"
#include "Game.h"
#include <vector>
#include <string.h>
#include <cstdlib>

#define FIRST 1
#define SECOND 2
#define FOUR 4
#define BUFFERSIZE 200

typedef struct CommandAndArgs {
    string command;
    vector<string> args;
}CommandAndArgs;

typedef struct HandleArgs {
    int socket;
    Game* game;
    vector<Game*> *games;
}HandleArgs;

class Handler {
public:
    void run(int clientSocket);
    static void *handleClient(void* socket);
    static void *handleGame(void* gameToHandle);
private:
    //Server serverToHandle;
    vector<Game*> games;
    static CommandAndArgs extractCommandAndArgs(char* buffer);
    static void deleteGame(vector<Game*> &games, string gameName);
};


#endif //ADVANCEDPROGRAMMING1_HANDLER_H
