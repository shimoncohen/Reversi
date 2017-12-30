// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Server.h"

pthread_mutex_t lockServer;

Server::Server(int port): port(port), serverSocket(0) {
    cout << "GameServer" << endl;
    running = 1;
}

void Server::runServer() {
    pthread_t thread;
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    Handler handler;
    int *clientSocket = new int[1];
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    cout << "In runServer:\nlistening to port\n" << endl;
    Info *info = new Info();
    info->handler = &handler;
    info->running = &running;
    try {
        pthread_create(&thread, NULL, waitForCloseMessage, (void *)info);
    } catch (const char *msg) {
        delete clientSocket;
        throw msg;
    }
    // Accept a new client connection
    AcceptStruct *acceptStruct = new AcceptStruct();
    acceptStruct->serverSocket = &serverSocket;
    acceptStruct->clientSocket = clientSocket;
    acceptStruct->running = &running;
    acceptStruct->handler = &handler;
    try {
        pthread_create(&thread, NULL, acceptNewClient, (void *) acceptStruct);
    } catch (const char *msg) {
        delete clientSocket;
        throw msg;
    }
    // as long as exit command has not been entered
    while(running);
    delete clientSocket;
}

void* Server::acceptNewClient(void *acceptStruct) {
    struct sockaddr_in firstClientAddress;
    socklen_t firstClientAddressLen;
    AcceptStruct *acceptStruct1 = (AcceptStruct*)acceptStruct;
    int serverSocket = *acceptStruct1->serverSocket;
    Handler *handler = acceptStruct1->handler;
    while (*acceptStruct1->running) {
        cout << "Waiting for client connections..." << endl;
        // accepting the client
        *acceptStruct1->clientSocket = accept(serverSocket, (struct sockaddr *) &firstClientAddress,
                                              &firstClientAddressLen);
        try {
            handler->run(*acceptStruct1->clientSocket);
        } catch (const char* msg) {
            throw msg;
        }
    }
}

void *Server::waitForCloseMessage(void* info) {
    Info *info1 = (Info*)info;
    string close;
    // waiting to receive "exit"
    do {
        cin >> close;
    } while(close.compare("exit") != 0);
    // close all of the servers threads
    info1->handler->closeThreads();
    // let server know that exit command has been entered
    *info1->running = 0;
}

void Server::stop() {
    close(serverSocket);
}