//
// Created by shimon on 12/20/17.
//

#ifndef ADVANCEDPROGRAMMING1_SERVER_H
#define ADVANCEDPROGRAMMING1_SERVER_H

#include "CommandsManager.h"
#include "Game.h"
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
    void runServer();
    static void *handleClient(void* socket);
    static void *handleGame(void* gameToHandle);
    /*
	 * function name: stop.
	 * input: none.
	 * output: none.
     * operation: Stops the server's activity.
    */
    void stop();
private:
    int port;
    int serverSocket;
    CommandsManager cm;
    vector<Game> games;
};


#endif //ADVANCEDPROGRAMMING1_SERVER_H