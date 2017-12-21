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
    int playerNum, n;
    string startString = "Start";
    char* start = new char[5], *temp = new char [5];
    strcpy(start, startString.c_str());
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
    // reading the player's number
    n = read(clientSocket, &playerNum, sizeof(playerNum));
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
    // recieve start game message
    while(strcmp(temp, start) != 0) {
        n = read(clientSocket, temp, sizeof(temp));
        if (n == -1) {
            throw "Error reading start game";
        }
    }
    free(start);
    free(temp);
}

void ServerPlayer::recieveOpponentsMove(int x, int y) {
    Info info;
    info.x = x;
    info.y = y;
    string play = "Play ";
    int temp = x;
    const char *message;
    char num;
    while(temp > 0) {
        temp %= 10;
        num =  (char)(temp + 48);
        play = play + num;
        temp /= 10;
    }
    play = play + " ";
    temp = y;
    while(temp > 0) {
        temp %= 10;
        num =  (char)(temp + 48);
        play = play + num;
        temp /= 10;
    }
    message = play.c_str();
// Write the exercise arguments to the socket
    if(x != -10 && y != -10) {
        int n = write(clientSocket, message, sizeof(message));
        if (n == -1) {
            throw "Error writing x to socket";
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
    do {
        n = read(clientSocket, &newInfo, sizeof(Info));
        if (n == -1) {
            throw "Error reading x from socket";
        }
        if (n == 0) {
            throw "Error, opponent disconnected!";
        }
    } while(newInfo.x < 0 || newInfo.y < 0);
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
    while(newInfo.x > board.getSize() || newInfo.y > board.getSize()) {
        newInfo = getMove();
    }
    int* move = new int[2];
    move[0] = newInfo.x;
    move[1] = newInfo.y;
    return move;
}

bool ServerPlayer::needPrint() {
    return false;
}