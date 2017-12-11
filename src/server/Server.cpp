// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Server.h"

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
    struct sockaddr_in firstClientAddress;
    struct sockaddr_in secondClientAddress;
    socklen_t firstClientAddressLen;
    socklen_t secondClientAddressLen;
    int playerNum = FIRST;
    string board;
    int temp;
    int x, y;
    while (true) {
        x = 0, y = 0;
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int firstClientSocket = accept(serverSocket, (struct sockaddr *) &firstClientAddress, &firstClientAddressLen);
        int n = write(firstClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        cout << "First player connected" << endl;
        if (firstClientSocket == -1)
            throw "Error on accept";
        //assigning the second player.
        playerNum = SECOND;
        int secondClientSocket = accept(serverSocket, (struct sockaddr *) &secondClientAddress,
                                        &secondClientAddressLen);
        n = write(secondClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        n = write(firstClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        n = write(secondClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        cout << "Second player connected" << endl;
        if (secondClientSocket == -1)
            throw "Error on accept";
        int currentClient = firstClientSocket;
        int waitingClient = secondClientSocket;
        while(x != -2 || y != -2) {
            if(handleClient(currentClient, &x, &y)) {
                break;
            }
            if(writeToClient(waitingClient, &x, &y)) {
                break;
            }
            temp = currentClient;
            currentClient = waitingClient;
            waitingClient = temp;
        }
        // end of game
        // Close communication with the client.
        close(firstClientSocket);
        close(secondClientSocket);
        playerNum = FIRST;
    }
}

// Handle requests from a specific client
int Server::handleClient(int clientSocket, int *x, int *y) {
    Info info;
    //read the info sent from the client.
    int n = read(clientSocket, &info, sizeof(Info));
    if (n == -1) {
        return 0;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return 1;
    }
    *x = info.x;
    *y = info.y;
    if(*x == -1 && *y == -1) {
        cout << "Player has no move" << endl;
    } else if(*x == -2 && *y == -2) {
        cout << "Got end of game info" << endl;
    } else {
        cout << "Got info: " << "move " << *x + 1 << " " << *y + 1 << endl;
    }
    return 0;
}

int Server::writeToClient(int clientSocket, int *x, int *y) {
    Info info;
    info.x = *x;
    info.y = *y;
    //write the info from one client to the other.
    int n = write(clientSocket, &info, sizeof(Info));
    if (n == -1) {
        return 0;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return 1;
    }
    if(*x == -1 && *y == -1) {
        cout << "Opponent had no move" << endl;
    } else if(*x == -2 && *y == -2) {
        cout << "Wrote end of game info" << endl;
    } else {
        cout << "Wrote info: " << "move " << *x + 1 << " " << *y + 1 << endl;
    }
    return 0;
}

void Server::stop() {
    close(serverSocket);
}