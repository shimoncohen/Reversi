// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Handler.h"

void Handler::run(int clientSocket) {
    pthread_mutex_t gamesLock;
    int n;
    pthread_t thread;
    HandleArgs *handleArgs = new HandleArgs();

    pthread_mutex_lock(&gamesLock);
    handleArgs->games = &games;
    pthread_mutex_unlock(&gamesLock);

    handleArgs->game = NULL;
    handleArgs->socket = clientSocket;
    //handleArgs->threadVector = &threadVector;
    try {
        n = pthread_create(&thread, NULL, handleClient, (void*)handleArgs);
    } catch (const char* msg) {
        throw msg;
    }
    if (n) {
        cout << "Error: unable to create thread" << endl;
        exit(-1);
    }
//    int i = 0;
//    Game* game = NULL;
//    for(i; i < games.size(); i++) {
//        if(games[i]->getFirstPlayer() == clientSocket || games[i]->getSecondPlayer() == clientSocket) {
//            game = games[i];
//        }
//    }
//    if(game != NULL) {
////        handleArgs->games = games;
////        handleArgs->socket = clientSocket;
//        try {
//            n = pthread_create(&thread, NULL, handleGame, (void *) handleArgs);
//        } catch (const char* msg) {
//            throw msg;
//        }
//    }
//    if (n) {
//        cout << "Error: unable to create thread" << endl;
//        exit(-1);
//    }
}

void* Handler::handleClient(void* handleArgs) {
    pthread_mutex_t gamesLock;
    CommandsManager cm;
    CommandAndArgs commandAndArgs;
    //vector<string> tempArguments;
    char buffer[BUFFERSIZE];
    string command, arguments[SECOND];
    HandleArgs *handleArgs1 = (HandleArgs*)handleArgs;

    pthread_mutex_lock(&gamesLock);
    vector<Game*>& temp = *handleArgs1->games;
    pthread_mutex_unlock(&gamesLock);
    //vector<pthread_t*> &threadTemp = *handleArgs1->threadVector;
    int i = 0, args = 0;
    int n = read(handleArgs1->socket, buffer, BUFFERSIZE*sizeof(char));
    //cout << "In handleClient:" << endl << "read from client: " << &buffer << endl;
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return NULL;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return NULL;
    }
    commandAndArgs = extractCommandAndArgs(buffer);
//    cout << "In handleClient:\nextracted command and arguments:\ncommand: " << commandAndArgs.command
//         << "\narguments: " << commandAndArgs.args[0] << " " << commandAndArgs.args[1] << endl;
    try {
        cm.executeCommand(commandAndArgs.command, commandAndArgs.args, temp, /*threadTemp,*/
                          handleArgs1->socket);
    } catch (const char* msg) {
        throw msg;
    }
//    int playerNum = FIRST;
//    int n = write((int)socket, &playerNum, sizeof(playerNum));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return NULL;
//    }
//    cout << "First player connected" << endl;
//    if ((int)socket == -1)
//        throw "Error on accept";
}

void* Handler::handleGame(void* handleArgs) {
    pthread_mutex_t gamesLock;
    CommandsManager cm;
    CommandAndArgs commandAndArgs;
    HandleArgs *handleArgs1 = (HandleArgs*)handleArgs;
    //vector<pthread_t*> &threadTemp = *handleArgs1->threadVector;
    //vector<string> arguments;
    int n, temp, i = 0;
    int playerNum = FIRST, firstPlayer, secondPlayer;
    //int x = 0, y = 0, temp;
    //int i = 0, tempX = 0, tempY = 0, flag = 0;
    string startMessage = STARTMESSAGE;
    char buffer[BUFFERSIZE];
    // lock the vector of games
    pthread_mutex_lock(&gamesLock);
    Game *currentGame = handleArgs1->game;
    // unlock the vector of games
    firstPlayer = currentGame->getFirstPlayer();
    secondPlayer = currentGame->getSecondPlayer();
    pthread_mutex_unlock(&gamesLock);

    write(firstPlayer, &playerNum, sizeof(int));
    playerNum = SECOND;
    write(secondPlayer, &playerNum, sizeof(int));
    //write(secondPlayer, &playerNum, sizeof(int));
    //n = write(currentGame->getFirstPlayer(), &startMessage, sizeof(startMessage));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return NULL;
//    }
    //cout << "In handleGame:\nsent message: " << startMessage << "to first player" << endl;

    //n = write(currentGame->getSecondPlayer(), &startMessage, sizeof(startMessage));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return NULL;
//    }
    //cout << "In handleGame:\nsent message: " << startMessage << "to second player" << endl;

    if (currentGame->getSecondPlayer() == -1)
        throw "Error on accept";
    int currentClient = currentGame->getFirstPlayer();
    int waitingClient = currentGame->getSecondPlayer();
    //while(x != -2 || y != -2) {
    do {
        //read the info sent from the client.
        int n = read(currentClient, buffer, BUFFERSIZE*sizeof(char));
        if (n == -1) {
            return NULL;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return NULL;
        }
        //cout << "In handleGame:\nread: " << buffer << endl;
//        while(buffer[i] != '\0') {
//            command.append(buffer[i]);
//            //command = command + buffer[i];
//            i++;
//        }
        commandAndArgs = extractCommandAndArgs(buffer);
//        cout << "In handleGame:\nextracted command and arguments:\ncommand: " << commandAndArgs.command
//             << "\narguments: " << commandAndArgs.args[0] << " " << commandAndArgs.args[1] << endl;
        if(commandAndArgs.command.compare("End") != 0 && commandAndArgs.command.compare("NoMoves") != 0) {
            try {
                cm.executeCommand(commandAndArgs.command, commandAndArgs.args,
                                  *handleArgs1->games, /*threadTemp,*/ currentClient);
            } catch (const char *msg) {
                throw msg;
            }
        }
//        for(i; i < BUFFERSIZE && buffer[i] != '\0'; i++) {
//            if(flag == 1 && buffer[i] == ' ') {
//                flag = 2;
//            }
//            if(flag != 2 && buffer[i] >= 48 && buffer[i] <= 58) {
//                tempX *= tempX;
//                tempX += buffer[i] - 48;
//                flag = 1;
//            }
//            if(flag == 2 && buffer[i] >= 48 && buffer[i] <= 58) {
//                tempY *= tempY;
//                tempY += buffer[i] - 48;
//                flag = 1;
//            }
//        }
//        x = tempX;
//        y = tempY;
//        if(x == -1 && y == -1) {
//            cout << "Player has no move" << endl;
//        } else if(x == -2 && y == -2) {
//            cout << "Got end of game info" << endl;
//        } else {
//            cout << "Got info: " << "move " << x + 1 << " " << y + 1 << endl;
//        }
        temp = currentClient;
        currentClient = waitingClient;
        waitingClient = temp;
    } while(strcmp(commandAndArgs.command.c_str(), "End") != 0);

    ///////////////send command to CM//////////////

    // end of game
    // Close communication with the client.
    pthread_mutex_lock(&gamesLock);
    deleteGame(*handleArgs1->games, handleArgs1->game->getName());
    pthread_mutex_unlock(&gamesLock);

    close(currentGame->getFirstPlayer());
    close(currentGame->getSecondPlayer());
    //delete gameToHandle;
}

CommandAndArgs Handler::extractCommandAndArgs(char* buffer) {
    int i = 0, args = 0;
    string startMessage = STARTMESSAGE, command, arguments[FOUR];
    CommandAndArgs commandAndArgs;
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
    } // play 3 2 , i = 4
    if(buffer[i] != '\0') {
        i++; // i = 5
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
    commandAndArgs.command = command;
    for(int j = 0; j <= args; j++) {
        if(arguments[j].compare("") != 0) {
            commandAndArgs.args.push_back(arguments[j]);
        }
    }
//    if(args == 0 && arguments[0].compare("") != 0) {
//        commandAndArgs.args.push_back(arguments[0]);
//    }
//    if(args == 1 && arguments[1].compare("") != 0) {
//        commandAndArgs.args.push_back(arguments[0]);
//        commandAndArgs.args.push_back(arguments[1]);
//    }
    return commandAndArgs;
}

void Handler::deleteGame(vector<Game*> &games, string gameName) {
    pthread_mutex_t gamesLock;
    int i = 0;
    pthread_mutex_lock(&gamesLock);
    for (i; i < games.size(); i++) {
        if (games.at(i)->getName().compare(gameName) == 0) {
            games.erase(games.begin() + i);
        }
    }
    pthread_mutex_unlock(&gamesLock);
}