// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "ServerPlayer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;

ServerPlayer::ServerPlayer(const char *serverIP, int serverPort):
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0), playerType(notDefined) {
     try{
         connectToServer();
     } catch (const char *msg) {
         throw msg;
     }
}

void ServerPlayer::connectToServer() {
// Create a socket point
    ConsolePrinter printer;
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
    // reading the player's number
    int n = read(clientSocket, &playerNum, sizeof(playerNum));
    if (n == -1) {
        throw "Error reading player num";
    }
    printer.connectedToServerMessage();
    if(playerNum == 1) {
        printer.waitingForConnectionMessage();
        playerType = whitePlayer;
    } else if(playerNum == 2) {
        playerType = blackPlayer;
    }
    n = read(clientSocket, &playerNum, sizeof(playerNum));
    if (n == -1) {
        throw "Error reading start game";
    }
}

void ServerPlayer::recieveOpponentsMove(int x, int y) {
// Write the exercise arguments to the socket
    if(x != -10 && y != -10) {
        int n = write(clientSocket, &x, sizeof(int));
        if (n == -1) {
            throw "Error writing x to socket";
        }
        n = write(clientSocket, &y, sizeof(int));
        if (n == -1) {
            throw "Error writing y to socket";
        }
        if (n == 0) {
            throw "Error, opponent disconnected!";
        }
    }
}

Info ServerPlayer::getMove() {
    Printer *printer = new ConsolePrinter;
    printer->waitingMessage();
    delete printer;
    //Read the result from the server
    int n;
    Info newInfo;
    n = read(clientSocket, &newInfo.x, sizeof(int));
    if (n == -1) {
        throw "Error reading x from socket";
    }
    n = read(clientSocket, &newInfo.y, sizeof(int));
    if (n == -1) {
        throw "Error reading y from socket";
    }
    if (n == 0) {
        throw "Error, opponent disconnected!";
    }
    return newInfo;
}

void ServerPlayer::assignType(type playerType1) {
    playerType = playerType1;
}

type ServerPlayer::getType() {
    return playerType;
}

int* ServerPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    Info newInfo = getMove();
    int* move = new int[2];
    move[0] = newInfo.x;
    move[1] = newInfo.y;
    return move;
}

bool ServerPlayer::needPrint() {
    return false;
}