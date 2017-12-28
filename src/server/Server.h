//
// Created by shimon on 12/20/17.
//

#ifndef ADVANCEDPROGRAMMING1_SERVER_H
#define ADVANCEDPROGRAMMING1_SERVER_H

#include "CommandsManager.h"
#include "Game.h"
#include "Handler.h"
#include <string.h>
#include <cstdlib>
#include <pthread.h>
#define MAX_CONNECTED_CLIENTS 10
#define THREADS_NUM 5
#define STARTMESSAGE "Start"
#define BUFFERSIZE 200
#define FIRST 1
#define SECOND 2

typedef struct Info {
    int x;
    int y;
}Info;

class Server {
public:
    Server(int port);
    //~Server();
    void runServer();
    //static void *handleClient(void* handleArgs);
    //static void *handleGame(void* handleArgs);
    //vector<Game*> getGameVector();
    //CommandsManager getCommandManager();
    /*
	 * function name: stop.
	 * input: none.
	 * output: none.
     * operation: Stops the server's activity.
    */
    void stop();
    //static void *handleAccepts(void* serverSocket);
private:
    int port;
    int serverSocket;
    //CommandsManager cm;
    //vector<Game*> games;
    //static CommandAndArgs extractCommandAndArgs(char* buffer);
};


#endif //ADVANCEDPROGRAMMING1_SERVER_H