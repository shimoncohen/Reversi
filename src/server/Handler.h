//
// Created by shimon on 12/23/17.
//

#ifndef ADVANCEDPROGRAMMING1_HANDLER_H
#define ADVANCEDPROGRAMMING1_HANDLER_H

#include "CommandsManager.h"
#include "Game.h"
#include <vector>
#include <string.h>

#define FIRST 1
#define SECOND 2
#define BUFFERSIZE 200

typedef struct CommandAndArgs {
    string command;
    vector<string> args;
}CommandAndArgs;

class Handler {
public:
    //Handler(Server server);
    static void *handleClient(void* socket);
    static void *handleGame(void* gameToHandle);
private:
    //Server serverToHandle;
    static CommandAndArgs extractCommandAndArgs(char* buffer);
};


#endif //ADVANCEDPROGRAMMING1_HANDLER_H
