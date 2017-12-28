// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Server.h"

Server::Server(int port): port(port), serverSocket(0) {
    cout << "GameServer" << endl;
}

void Server::runServer() {
    pthread_t thread;
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in firstClientAddress;
    socklen_t firstClientAddressLen;
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
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        *clientSocket = accept(serverSocket, (struct sockaddr *) &firstClientAddress, &firstClientAddressLen);
        //cout << "In runServer:" << endl << "accepted new client" << endl << endl;
        try {
            handler.run(*clientSocket);
        } catch (const char* msg) {
            throw msg;
        }
    }
    delete clientSocket;
}

//void Server::handleAccepts(void* serverSocket) {
//    struct sockaddr_in firstClientAddress;
//    socklen_t firstClientAddressLen;
//    Handler handler;
//    int *clientSocket = new int[1];
//    int socket = *(int*)serverSocket;
//    const char* error;
//    bool errorFlag = false;
//    while (true) {
//        cout << "Waiting for client connections..." << endl;
//        // Accept a new client connection
//        *clientSocket = accept(socket, (struct sockaddr *) &firstClientAddress, &firstClientAddressLen);
//        //cout << "In runServer:" << endl << "accepted new client" << endl << endl;
//        try {
//            handler.run(*clientSocket);
//        } catch (const char* msg) {
//            error = msg;
//            errorFlag = true;
//        }
//        if(errorFlag) {
//            break;
//        }
//    }
//    delete clientSocket;
//    throw error;
//}

void Server::stop() {
    close(serverSocket);
}