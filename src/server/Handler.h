// 315383133 shimon cohen
// 302228275 Nadav Spitzer

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
    vector<pthread_t*> *threadVector;
}HandleArgs;

class Handler {
public:
    void run(int clientSocket);
    static void *handleClient(void* socket);
    static void *handleGame(void* gameToHandle);
private:
    vector<Game*> games;
    vector<pthread_t*> threadVector;
    void printThreadVectorSize();
    static CommandAndArgs extractCommandAndArgs(char* buffer);
    static void deleteGame(vector<Game*> &games, string gameName);
    static void deleteThread(vector<pthread_t*> &threads, pthread_t pthread);
};


#endif //ADVANCEDPROGRAMMING1_HANDLER_H
