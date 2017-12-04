// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "ServerPlayer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;

ServerPlayer::ServerPlayer(const char *serverIP, int serverPort, type type1):
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0), playerType(type1) {
    cout << "Client" << endl;
}

void ServerPlayer::connectToServer() {
// Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
// Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
// htons converts values between host and network byteorders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    int playerNum;
    int n = read(clientSocket, &playerNum, sizeof(playerNum));
    if (n == -1) {
        throw "Error reading player num";
    }
    if(playerNum == 1) {
        playerType = blackPlayer;
    } else if(playerNum == 2) {
        playerType = whitePlayer;
    }
    cout << "Connected to server" << endl;
    cout << "You are player number " << playerNum << endl;
}

Info ServerPlayer::sendMove(Board &board, int x, int y) {
// Write the exercise arguments to the socket
    int n = write(clientSocket, &board, sizeof(board));
    if (n == -1) {
        throw "Error writing arg1 to socket";
    }
    n = write(clientSocket, &x, sizeof(x));
    if (n == -1) {
        throw "Error writing op to socket";
    }
    n = write(clientSocket, &y, sizeof(y));
    if (n == -1) {
        throw "Error writing arg2 to socket";
    }
    //Read the result from the server
    Info newInfo;
    n = read(clientSocket, &newInfo.board, sizeof(newInfo.board));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    n = read(clientSocket, &newInfo.x, sizeof(newInfo.x));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    n = read(clientSocket, &newInfo.y, sizeof(newInfo.y));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return newInfo;
}

Info ServerPlayer::getMove() {
    //Read the result from the server
    int n;
    Info newInfo;
    n = read(clientSocket, &newInfo.board, sizeof(newInfo.board));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    n = read(clientSocket, &newInfo.x, sizeof(newInfo.x));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    n = read(clientSocket, &newInfo.y, sizeof(newInfo.y));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return newInfo;
}

type ServerPlayer::getType() {
    return playerType;
}

int* ServerPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    string temp1, temp2;
    int *choice = new int[2];
    choice[0] = 0;
    choice[1] = 0;
    cin >> temp1 >> temp2;
    //check if what the user entered are numbers.
    for (int i = 0; i < temp1.size(); i++) {
        if (!isdigit(temp1[i])) {
            choice[0] = 0;
            choice[1] = 0;
            return choice;
        }
    }
    for (int i = 0; i < temp2.size(); i++) {
        if (!isdigit(temp2[i])) {
            choice[0] = 0;
            choice[1] = 0;
            return choice;
        }
    }
    //if the user entered numbers the convert them to int.
    for(int i = 0; i < temp1.size(); i++) {
        choice[0] *= 10;
        choice[0] += temp1[i] - 48;
    }
    for(int i = 0; i < temp2.size(); i++) {
        choice[1] *= 10;
        choice[1] += temp2[i] - 48;
    }
    return choice;
}