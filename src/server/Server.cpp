//
// Created by shimon on 12/3/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#define FIRST 1
#define SECOND 2

using namespace std;
#define MAX_CONNECTED_CLIENTS 10
Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
// Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
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
// Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    int playerNum = FIRST;
    while (true) {
        cout << "Waiting for client connections..." << endl;
// Accept a new client connection
        int firstClientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        int n = write(firstClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        cout << "First player connected" << endl;
        if (firstClientSocket == -1)
            throw "Error on accept";
        playerNum = SECOND;
        int secondClientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        n = write(secondClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        cout << "Second player connected" << endl;
        if (secondClientSocket == -1)
            throw "Error on accept";
        handleClient(firstClientSocket, secondClientSocket);
// Close communication with the client
        close(firstClientSocket);
        close(secondClientSocket);
        playerNum = 1;
    }
}

// Handle requests from a specific client
void Server::handleClient(int firstClientSocket, int secondClientSocket) {
    string board;
    int x, y, temp;
    int currentClient = firstClientSocket;
    int waitingClient = secondClientSocket;
    while (true) {
// Read new exercise arguments
        int n = read(currentClient, &board, sizeof(board));
        if (n == -1) {
            cout << "Error reading arg1" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        n = read(currentClient, &x, sizeof(x));
        if (n == -1) {
            cout << "Error reading x" << endl;
            return;
        }
        n = read(currentClient, &y, sizeof(y));
        if (n == -1) {
            cout << "Error reading y" << endl;
            return;
        }
        cout << "Got info: " << "board and move " << x << " " << y << endl;
        // Write the information back to the client
        n = write(waitingClient, &board, sizeof(board));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        n = write(waitingClient, &x, sizeof(x));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        n = write(waitingClient, &y, sizeof(y));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        temp = currentClient;
        currentClient = waitingClient;
        waitingClient = temp;
    }
}

//int Server::calc(int arg1, const char op, int arg2) const {
//    switch (op) {
//        case '+':
//            return arg1 + arg2;
//        case '-':
//            return arg1 - arg2;
//        case '*':
//            return arg1 * arg2;
//        case '/':
//            return arg1 / arg2;
//        default:
//            cout << "Invalid operator" << endl;
//            return 0;
//    }
//}

void Server::stop() {
    close(serverSocket);
}