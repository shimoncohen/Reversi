// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Handler.h"

pthread_mutex_t gamesLockHander;

void Handler::run(int clientSocket) {
    int n;
    pthread_t thread;
    HandleArgs *handleArgs = new HandleArgs();
    pthread_mutex_trylock(&gamesLockHander);
    handleArgs->games = &games;
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_trylock(&gamesLockHander);
    handleArgs->threadVector = &threadVector;
    pthread_mutex_unlock(&gamesLockHander);
    handleArgs->game = NULL;
    handleArgs->socket = clientSocket;
    try {
        n = pthread_create(&thread, NULL, handleClient, (void*)handleArgs);
    } catch (const char* msg) {
        throw msg;
    }
    if (n) {
        cout << "Error: unable to create thread" << endl;
        exit(-1);
    }
    //printThreadVectorSize();
}

void* Handler::handleClient(void* handleArgs) {
    CommandsManager cm;
    CommandAndArgs commandAndArgs;
    vector<string> tempArguments;
    char buffer[BUFFERSIZE];
    string command;
    HandleArgs *handleArgs1 = (HandleArgs*)handleArgs;
    pthread_mutex_lock(&gamesLockHander);
    vector<Game*>& temp = *handleArgs1->games;
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_lock(&gamesLockHander);
    vector<pthread_t*> &threadTemp = *handleArgs1->threadVector;
    pthread_mutex_unlock(&gamesLockHander);
    int n = read(handleArgs1->socket, buffer, BUFFERSIZE*sizeof(char));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return NULL;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return NULL;
    }
    commandAndArgs = extractCommandAndArgs(buffer);
    try {
        cm.executeCommand(commandAndArgs.command, commandAndArgs.args, temp, threadTemp,
                          handleArgs1->socket);
    } catch (const char* msg) {
        throw msg;
    }
}

void* Handler::handleGame(void* handleArgs) {
    CommandsManager cm;
    CommandAndArgs commandAndArgs;
    HandleArgs *handleArgs1 = (HandleArgs*)handleArgs;
    int n, temp;
    int playerNum = FIRST, firstPlayer, secondPlayer;
    string startMessage = STARTMESSAGE;
    char buffer[BUFFERSIZE];
    // lock the vector of games
    pthread_mutex_lock(&gamesLockHander);
    Game *currentGame = handleArgs1->game;
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_lock(&gamesLockHander);
    vector<pthread_t*> &threadTemp = *handleArgs1->threadVector;
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_lock(&gamesLockHander);
    vector<Game*> &tempGames = *handleArgs1->games;
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_lock(&gamesLockHander);
    firstPlayer = currentGame->getFirstPlayer();
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_lock(&gamesLockHander);
    secondPlayer = currentGame->getSecondPlayer();
    pthread_mutex_unlock(&gamesLockHander);

    n = write(firstPlayer, &playerNum, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return NULL;
    }
    playerNum = SECOND;
    n = write(secondPlayer, &playerNum, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return NULL;
    }
    if (secondPlayer == -1)
        throw "Error on accept";
    int currentClient = firstPlayer;
    int waitingClient = secondPlayer;
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
        commandAndArgs = extractCommandAndArgs(buffer);
        if(commandAndArgs.command.compare("End") != 0 && commandAndArgs.command.compare("NoMoves") != 0) {
            try {
                cm.executeCommand(commandAndArgs.command, commandAndArgs.args,
                                  tempGames, threadTemp, currentClient);
            } catch (const char *msg) {
                throw msg;
            }
        }
        temp = currentClient;
        currentClient = waitingClient;
        waitingClient = temp;
    } while(strcmp(commandAndArgs.command.c_str(), "End") != 0
            && strcmp(commandAndArgs.command.c_str(), "close") != 0);
    // end of game
    // Close communication with the client.
    pthread_mutex_lock(&gamesLockHander);
    deleteGame(*handleArgs1->games, handleArgs1->game->getName());
    pthread_mutex_unlock(&gamesLockHander);
    pthread_mutex_lock(&gamesLockHander);
    deleteThread(*handleArgs1->threadVector, handleArgs1->game->getThread());
    pthread_mutex_unlock(&gamesLockHander);

    close(firstPlayer);
    close(secondPlayer);
    pthread_exit(NULL);
}

CommandAndArgs Handler::extractCommandAndArgs(char* buffer) {
    int i = 0, args = 0;
    string startMessage = STARTMESSAGE, command, arguments[FOUR];
    CommandAndArgs commandAndArgs;
    for(i; i < BUFFERSIZE; i++) {
        if(buffer[i] != '\0') {
            if(buffer[i] != ' ') {
                command.append(sizeof(char) ,buffer[i]);
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
    return commandAndArgs;
}

void Handler::deleteGame(vector<Game*> &games, string gameName) {
    int i = 0;
    pthread_mutex_lock(&gamesLockHander);
    for (i; i < games.size(); i++) {
        if (games.at(i)->getName().compare(gameName) == 0) {
            games.erase(games.begin() + i);
        }
    }
    pthread_mutex_unlock(&gamesLockHander);
}

void Handler::deleteThread(vector<pthread_t *> &threads, pthread_t pthread) {
    int i = 0;
    pthread_mutex_lock(&gamesLockHander);
    for (i; i < threads.size(); i++) {
        if (*threads.at(i) == pthread) {
            threads.erase(threads.begin() + i);
        }
    }
    pthread_mutex_unlock(&gamesLockHander);
}

//void Handler::printThreadVectorSize() {
//    cout << "threads: ";
//    pthread_mutex_lock(&gamesLockHander);
//    cout << threadVector.size() << endl;
//    pthread_mutex_unlock(&gamesLockHander);
//    cout << "games: ";
//    pthread_mutex_lock(&gamesLockHander);
//    cout << games.size() << endl;
//    pthread_mutex_unlock(&gamesLockHander);
//}