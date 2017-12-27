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
    int playerNum = 0, n = 0;
//    try {
//        connectToServer();
//    } catch(const char* msg) {
//        throw msg;
//    }
    // reading the player's number
    n = read(clientSocket, &playerNum, sizeof(int));
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
//    close(clientSocket);
//    clientSocket = 0;
}

void ServerPlayer::recieveOpponentsMove(int x, int y) {

    ////// try
    //connectToServer();
    ////// catch

    string play = "play ";
    const char *message;
    if(x == -2 && y == -2) {
        play = "End";
    } else if(x == -1 && y == -1) {
        play = "NoMoves";
    } else {
        int temp = x + 1;
        char num;
        while (temp > 0) {
            temp %= 10;
            num = (char) (temp + 48);
            play = play + num;
            temp /= 10;
        }
        play = play + " ";
        temp = y + 1;
        while (temp > 0) {
            temp %= 10;
            num = (char) (temp + 48);
            play = play + num;
            temp /= 10;
        }
    }
//    play = play + " " + gameName;
//    if(playerType == blackPlayer) {
//        play = play + " blackPlayer";
//    } else {
//        play = play + " whitePlayer";
//    }
    message = play.c_str();
// Write the exercise arguments to the socket
    if(x != -10 && y != -10) {
        int n = write(clientSocket, message, BUFFERSIZE*sizeof(char));
        if (n == -1) {
            throw "Error writing x to socket";
        }
        if (n == 0) {
            throw "Error, opponent disconnected!";
        }
    }

}

Info ServerPlayer::getMove() {

    ////// try
    //connectToServer();
    ////// catch

    //Read the result from the server
    int n, x, y;
    char buffer[BUFFERSIZE];
    Info newInfo;
    do {
        n = read(clientSocket, buffer, BUFFERSIZE*sizeof(char));
        if (n == -1) {
            throw "Error reading x from socket";
        }
        if (n == 0) {
            throw "Error, opponent disconnected!";
        }
        newInfo = extractCommandAndArgs(buffer);
    } while((newInfo.x < 0 || newInfo.y < 0) && (newInfo.x != -2 && newInfo.y != -2));
    return newInfo;
}

void ServerPlayer::assignType(type playerType1) {
    playerType = playerType1;
}

type ServerPlayer::getType() {
    return playerType;
}

int* ServerPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    ConsolePrinter printer;
    printer.waitingMessage();
    Info newInfo;
    do {
        newInfo = getMove();
    } while(newInfo.x > board.getSize() || newInfo.y > board.getSize()
            || gameLogic.validOption(board, newInfo.x + 1, newInfo.y + 1, moves) == false);
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
    try {
        connectToServer();
    } catch (const char* msg) {
        throw msg;
    }
    while(!flag) {
        // connecting to the server socket
//        try {
//            connectToServer();
//        } catch (const char* msg) {
//            throw msg;
//        }
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
        if (strcmp(recieve, "NotExist") == 0 || strcmp(recieve, "AlreadyExist") == 0) {
            printer.gameDeniedMessage(recieve);
            //closing the socket
            reconnect();
            continue;
        // in option "start" - entering a name that is already on the list
        }
        if(command == "list_games") {
            // reading the size of the list
            n = read(clientSocket, &sizeOfList, sizeof(sizeOfList));
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
            // for problems with reading from the socket
            if (n == -1) {
                throw "Error reading command from socket";
            }
            if (n == 0) {
                throw "Error, connection disconnected!";
            }
            printer.printGamesList(sizeOfList, list);
            free(list);
            reconnect();
            continue;
        }
        // if the input was legal
        flag = true;
    }
    cout << "received command is: " << command << endl;
    //if(command == "start" || command == "join") {
    //gameName = name;
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

Info ServerPlayer::extractCommandAndArgs(char* buffer) {
    Info parsed;
    int i = 0, args = 0;
    string command, arguments[TWO];
    for(i; i < BUFFERSIZE; i++) {
        if(buffer[i] != '\0') {
            if(buffer[i] != ' ') {
                command.append(sizeof(char) ,buffer[i]);
                //command = command + buffer[i];
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if(buffer[i] != '\0') {
        i++;
    }
    for(i; i < BUFFERSIZE; i++) {
        if(buffer[i] != '\0') {
            if(buffer[i] != ' ') {
                arguments[args].append(sizeof(char), buffer[i]);
                //arguments[args] = arguments[args] + buffer[i];
            } else {
                args += 1;
            }
        } else {
            break;
        }
    }
//    if(args == 0 && arguments[0].compare("") != 0) {
//        parsed.x = atoi(arguments[0].c_str());
//    }
    if(args == 1 && arguments[1].compare("") != 0) {
        parsed.x = atoi(arguments[0].c_str()) - 1;
        parsed.y = atoi(arguments[1].c_str()) - 1;
    }
    return parsed;
}

void ServerPlayer::reconnect() {
    close(clientSocket);
    clientSocket = 0;
    try {
        connectToServer();
    } catch (const char* msg) {
        throw msg;
    }
}