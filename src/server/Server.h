// 315383133 shimon cohen
// 302228275 Nadav Spitzer

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
    Handler *handler;
    int *running;
}Info;

typedef struct AcceptStruct {
    Handler *handler;
    int *running;
    int *clientSocket;
    int *serverSocket;
}AcceptStruct;

class Server {
public:
    Server(int port);
    //~Server();
    void runServer();
    /*
	 * function name: stop.
	 * input: none.
	 * output: none.
     * operation: Stops the server's activity. closes the socket.
    */
    void stop();
    /*
	 * function name: acceptNewClient.
	 * input: a struct with info about the client we want to accept.
	 * output: none.
     * operation: receives a struct with client info and accepts a new client.
    */
    static void *acceptNewClient(void* acceptStruct);
    /*
	 * function name: waitForCloseMessage.
	 * input: a handler.
	 * output: none.
     * operation: the process waits for "exit" as input. when entered, closes all threads, games and the server.
    */
    static void *waitForCloseMessage(void* handler);
    //static void handleAccepts(void* serverSocket);
private:
    int port;
    int running;
    int serverSocket;
};


#endif //ADVANCEDPROGRAMMING1_SERVER_H