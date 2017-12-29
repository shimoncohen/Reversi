// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "GameServer.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define STARTMESSAGE "Start"
#define BUFFERSIZE 200

GameServer::GameServer(int port): port(port), serverSocket(0) {
    cout << "GameServer" << endl;
}

void GameServer::start() {
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
    // set first player num as 1
    int playerNum = FIRST;
    string board, startMessage = STARTMESSAGE;
    int temp;
    int x, y;
    while (true) {
        x = 0, y = 0;
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int firstClientSocket = accept(serverSocket, (struct sockaddr *) &firstClientAddress, &firstClientAddressLen);
        // sending message to the player about his position (first or second)
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
        // sending message to the player about his position (first or second)
        n = write(secondClientSocket, &playerNum, sizeof(playerNum));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        // sending start message to the player
        n = write(firstClientSocket, &startMessage, sizeof(startMessage));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        // sending start message to the player
        n = write(secondClientSocket, &startMessage, sizeof(startMessage));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
        cout << "Second player connected" << endl;
        if (secondClientSocket == -1)
            throw "Error on accept";
        // setting the order of the players (current player is the one playing, waiting player waits for his turn).
        int currentClient = firstClientSocket;
        int waitingClient = secondClientSocket;
        // -2 represents end of game.
        while(x != -2 || y != -2) {
            if(handleClient(currentClient, &x, &y)) {
                break;
            }
            if(writeToClient(waitingClient, &x, &y)) {
                break;
            }
            // switchig between the players
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
int GameServer::handleClient(int clientSocket, int *x, int *y) {
    Info info;
    char* buffer = new char[BUFFERSIZE];
    int i = 0, tempX = 0, tempY = 0, flag = 0;
    //read the info sent from the client.
    int n = read(clientSocket, buffer, BUFFERSIZE*sizeof(char));
    if (n == -1) {
        return 0;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return 1;
    }
    for(i; i < BUFFERSIZE && buffer[i] != '\0'; i++) {
        if(flag == 1 && buffer[i] == ' ') {
            flag = 2;
        }
        if(flag != 2 && buffer[i] >= 48 && buffer[i] <= 58) {
            tempX *= tempX;
            tempX += buffer[i] - 48;
            flag = 1;
        }
        if(flag == 2 && buffer[i] >= 48 && buffer[i] <= 58) {
            tempY *= tempY;
            tempY += buffer[i] - 48;
            flag = 1;
        }
    }
    *x = tempX;
    *y = tempY;
    if(*x == -1 && *y == -1) {
        cout << "Player has no move" << endl;
    } else if(*x == -2 && *y == -2) {
        cout << "Got end of game info" << endl;
    } else {
        cout << "Got info: " << "move " << *x + 1 << " " << *y + 1 << endl;
    }
    free(buffer);
    return 0;
}

int GameServer::writeToClient(int clientSocket, int *x, int *y) {
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
    // in case the player has no move -1,-1 was sent to him
    if(*x == -1 && *y == -1) {
        cout << "Opponent had no move" << endl;
    } else if(*x == -2 && *y == -2) {
        cout << "Wrote end of game info" << endl;
    } else {
        cout << "Wrote info: " << "move " << *x + 1 << " " << *y + 1 << endl;
    }
    return 0;
}

void GameServer::stop() {
    close(serverSocket);
}