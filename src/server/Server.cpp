// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Server.h"

Server::Server(int port): port(port), serverSocket(0) {
    cout << "GameServer" << endl;
}

void Server::runServer() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
    // Define the client socket's structures
    struct sockaddr_in firstClientAddress;
    socklen_t firstClientAddressLen;
    Handler handler;
    int *clientSocket;
    const char* error;
    bool errorFlag = false;
    // Define the client socket's structures
    while (true) {
        //cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        *clientSocket = accept(serverSocket, (struct sockaddr *) &firstClientAddress, &firstClientAddressLen);
        //cout << "In runServer:" << endl << "accepted new client" << endl << endl;
        try {
            handler.run(*clientSocket);
        } catch (const char* msg) {
            error = msg;
            errorFlag = true;
        }
        if(errorFlag) {
            break;
        }
//        int n;
//        pthread_t thread;
//        HandleArgs *handleArgs = new HandleArgs();
//        handleArgs->games = games;
//        handleArgs->socket = clientSocket;
//        n = pthread_create(&thread, NULL, handler.handleClient, (void*)handleArgs);
//        if (n) {
//            cout << "Error: unable to create thread" << endl;
//            exit(-1);
//        }
//        int i = 0;
//        Game* game = NULL;
//        for(i; i < games.size(); i++) {
//            if(games[i]->getFirstPlayer() == clientSocket || games[i]->getSecondPlayer() == clientSocket) {
//                game = games[i];
//            }
//        }
//        if(game != NULL) {
////        handleArgs->games = games;
////        handleArgs->socket = clientSocket;
//            n = pthread_create(&thread, NULL, handler.handleGame, (void *)handleArgs);
//        }
//        if (n) {
//            cout << "Error: unable to create thread" << endl;
//            exit(-1);
//        }
        //assigning the second player.
//        playerNum = SECOND;
//        int secondClientSocket = accept(serverSocket, (struct sockaddr *) &secondClientAddress,
//                                        &secondClientAddressLen);
//        n = write(secondClientSocket, &playerNum, sizeof(playerNum));
//        if (n == -1) {
//            cout << "Error writing to socket" << endl;
//            return;
//        }
    }
    throw error;
}

void Server::stop() {
    close(serverSocket);
}