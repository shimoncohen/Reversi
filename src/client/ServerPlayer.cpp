// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "ServerPlayer.h"


using namespace std;

ServerPlayer::ServerPlayer(const char *serverIP, int serverPort):
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0), playerType(notDefined) {
//    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (clientSocket == -1) {
//        throw "Error opening socket";
//    }
//    // Convert the ip string to a network address
//    struct in_addr address;
//    if (!inet_aton(serverIP, &address)) {
//        throw "Can't parse IP address";
//    }
//    // Get a hostent structure for the given host address
//    struct hostent *server;
//    server = gethostbyaddr((const void *) &address, sizeof
//            address, AF_INET);
//    if (server == NULL) {
//        throw "Host is unreachable";
//    }
//// Create a structure for the server address
//    struct sockaddr_in serverAddress;
//    bzero((char *) &address, sizeof(address));
//    serverAddress.sin_family = AF_INET;
//    memcpy((char *) &serverAddress.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
//// htons converts values between host and network byteorders
//    serverAddress.sin_port = htons(serverPort);
//    // Establish a connection with the TCP server
//    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
//        throw "Error connecting to server";
//    }
    // recieve start game message
//    while(strcmp(temp, start) != 0) {
//        n = read(clientSocket, temp, sizeof(temp));
//        if (n == -1) {
//            throw "Error reading start game";
//        }
//    }


    // starting the client's opperation
    try {
        clientMenu();
    } catch (const char* msg) {
        throw msg;
    }
}

void ServerPlayer::connectToServer() {
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
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
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
}

void ServerPlayer::startGame() {
// Create a socket point
    ConsolePrinter printer;
    int playerNum, n;
//    try {
//        connectToServer();
//    } catch(const char* msg) {
//        throw msg;
//    }
    // reading the player's number
    n = read(clientSocket, &playerNum, sizeof(playerNum));
    if (n == -1) {
        throw "Error reading player num";
    }
    cout << "player num: " << playerNum << endl;
    printer.connectedToServerMessage();
    if(playerNum == 1) {
        printer.waitingForConnectionMessage();
        playerType = whitePlayer;
    } else if(playerNum == 2) {
        playerType = blackPlayer;
    }
    close(clientSocket);
    clientSocket = 0;
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
    ConsolePrinter printer;
    printer.waitingMessage();
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

void ServerPlayer::clientMenu() {
    string command, name = "";
    const char* message;
    char *recieve = new char[BUFFERSIZE];
    int oper, n, sizeOfList;
    bool flag = false;
    ConsolePrinter printer;
    // printing client's menu before joining game
    while(!flag) {
        // connecting to the server socket
        try {
            connectToServer();
        } catch (const char* msg) {
            throw msg;
        }
        printer.printClientMenu();
        // get the operation of the client
        cin >> oper;
        if(oper == 1 || oper == 3) {
            cin >> name;
        }
        // translating the command from a number into string
        command = translateOperation(oper, name);
        while(command.compare("NotOption") == 0) {
            printer.gameNotOption();
            printer.printClientMenu();
            // get the operation of the client
            cin >> oper;
            if(oper == 1 || oper == 3) {
                cin >> name;
            }
            command = translateOperation(oper, name);
        }
        message = command.c_str();
        // sending the command to the server
        n = write(clientSocket, message, BUFFERSIZE*sizeof(char));
        if (n == -1) {
            throw "Error writing command to socket";
        }
        if (n == 0) {
            throw "Error, connection disconnected!";
        }
        // reading the servers answer from the socket
        if(oper == 1 || oper == 3) {
            do {
                n = read(clientSocket, recieve, BUFFERSIZE * sizeof(char));
            } while (strcmp(recieve, "") == 0);
        }
        // for problems with reading from the socket
        if (n == -1) {
            throw "Error reading command from socket";
        }
        if (n == 0) {
            throw "Error, connection disconnected!";
        }
        // in option "join" - entering a name that isn't on the list
        if (strcmp(recieve, "NotExist") == 0) {
            printer.gameNotExist();
            // closing the socket
            close(clientSocket);
            clientSocket = 0;
            continue;
        // in option "start" - entering a name that is already on the list
        } else if(strcmp(recieve, "AlreadyExist") == 0) {
            printer.gameAlreadyExist();
            // closing the socket
            close(clientSocket);
            clientSocket = 0;
            continue;
        // in case user entered an option not from the menu
        }
        if(command == "list_games") {
            // reading the size of the list
            n = read(clientSocket, &sizeOfList, sizeof(sizeOfList));
            cout << "In clientMenu:\nread message size: " << sizeOfList << endl;
            // for problems with reading from the socket
            if (n == -1) {
                throw "Error reading command from socket";
            }
            if (n == 0) {
                throw "Error, connection disconnected!";
            }
            char *list = new char[BUFFERSIZE];
            // reading the list in string display
            n = read(clientSocket, list, BUFFERSIZE * sizeof(char));
            cout << "In clientMenu:\nread message: " << list << endl;
            // for problems with reading from the socket
            if (n == -1) {
                throw "Error reading command from socket";
            }
            if (n == 0) {
                throw "Error, connection disconnected!";
            }
            printer.printGamesList(sizeOfList, list);
            free(list);
            close(clientSocket);
            clientSocket = 0;
            continue;
        }
        // if the input was legal
        flag = true;
    }
    cout << "received command is: " << command << endl;
    // closing the socket
//    close(clientSocket);
//    clientSocket = 0;
    //if(command == "start" || command == "join") {
    try {
        startGame();
    } catch (const char* msg) {
        throw msg;
    }
    //}
}

string ServerPlayer::translateOperation(int oper, string name) {
    switch(oper) {
        case 1:
            return "start " + name;
        case 2:
            return "list_games";
        case 3:
            return "join " + name;
        default:
            return "NotOption";
    }
}

int ServerPlayer::commandChooser(string com) {
    if(com.compare("start")) {
        return 1;
    } else if(com.compare("list")) {
        return 2;
    } else if(com.compare("join")) {
        return 3;
    }
}