// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Handler.h"

// creating mutexes
pthread_mutex_t gamesLockHandlerRun;
pthread_mutex_t gamesLockHandlerCloseThreads;
pthread_mutex_t gamesLockHandlerHandleClient;
pthread_mutex_t gamesLockHandlerHandleGame;
pthread_mutex_t gamesLockHandlerDeleteGame;
pthread_mutex_t gamesLockHandlerDeleteThread;

void Handler::run(int clientSocket) {
    int n;
    pthread_t thread;
    HandleArgs *handleArgs = new HandleArgs();
    pthread_mutex_lock(&gamesLockHandlerRun);
    handleArgs->games = &games;
    pthread_mutex_unlock(&gamesLockHandlerRun);
    pthread_mutex_lock(&gamesLockHandlerRun);
    handleArgs->threadVector = &threadVector;
    pthread_mutex_unlock(&gamesLockHandlerRun);
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
}

void Handler::closeThreads() {
    // locking the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLockHandlerCloseThreads);
    int size = games.size();
    for(int i = size - 1; i >= 0; i--) {
        int first = games[i]->getFirstPlayer();
        int second = games[i]->getSecondPlayer();
        if(second == 0) {
            write(first, CLOSE, CLOSESIZE * sizeof(char));

        } else {
            // sending close messages to both players.
            write(first, CLOSE, CLOSESIZE * sizeof(char));
            write(second, CLOSE, CLOSESIZE * sizeof(char));
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerCloseThreads);
    // locking the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLockHandlerCloseThreads);
    size = threadVector.size();
    for(int i = size - 1; i >= 0; i--) {
        threadVector.pop_back();
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerCloseThreads);
}

void* Handler::handleClient(void* handleArgs) {
    CommandsManager cm;
    CommandAndArgs commandAndArgs;
    char buffer[BUFFERSIZE] = {0};
    HandleArgs *handleArgs1 = (HandleArgs*)handleArgs;
    // locking the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLockHandlerHandleClient);
    vector<Game*>& temp = *handleArgs1->games;
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleClient);
    // locking the vector of threads to prevent changes.
    pthread_mutex_lock(&gamesLockHandlerHandleClient);
    vector<pthread_t*> &threadTemp = *handleArgs1->threadVector;
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleClient);
    // reading the command from the client.
    int n = read(handleArgs1->socket, buffer, BUFFERSIZE*sizeof(char));
    if (n == -1) {
        cout << "Error reading from socket" << endl;
        return NULL;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return NULL;
    }
    // converting the command.
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
    char buffer[BUFFERSIZE] = {0};
    // lock the vector of games.
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    vector<Game*> &tempGames = *handleArgs1->games;
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    vector<pthread_t*> &threadTemp = *handleArgs1->threadVector;
    // unloc the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    Game *currentGame = handleArgs1->game;
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);
    // lock the the current game.
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    firstPlayer = currentGame->getFirstPlayer();
    // unlock the game.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);
    // lock the current game.
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    secondPlayer = currentGame->getSecondPlayer();
    // unlock the game.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);
    // writing the position number to the first player.
    n = write(firstPlayer, &playerNum, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return NULL;
    }
    // writing the position number to the second player.
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
        // extracting the command from the buffer.
        commandAndArgs = extractCommandAndArgs(buffer);
        // we will exectue the command as long as it's not "End" or "NoMoves".
        if(commandAndArgs.command.compare("End") != 0 && commandAndArgs.command.compare("NoMoves") != 0) {
            try {
                // executing the command
                cm.executeCommand(commandAndArgs.command, commandAndArgs.args,
                                  tempGames, threadTemp, currentClient);
            } catch (const char *msg) {
                throw msg;
            }
        }
        // switching between the players.
        temp = currentClient;
        currentClient = waitingClient;
        waitingClient = temp;
    // end ing the game if the command is either "End" or "close".
    } while(strcmp(commandAndArgs.command.c_str(), "End") != 0
            && strcmp(commandAndArgs.command.c_str(), "close") != 0);
    // end of game
    // Close communication with the client.
    // lock the vector of games.
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    deleteGame(*handleArgs1->games, handleArgs1->game->getName());
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);
    // lock the vector of threads.
    pthread_mutex_lock(&gamesLockHandlerHandleGame);
    deleteThread(*handleArgs1->threadVector, handleArgs1->game->getThread());
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerHandleGame);

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
                // seperating the command from the string.
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
            // seperating the arguments.
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
    // inserting the arguments to a vector of strings.
    for(int j = 0; j <= args; j++) {
        if(arguments[j].compare("") != 0) {
            commandAndArgs.args.push_back(arguments[j]);
        }
    }
    return commandAndArgs;
}

void Handler::deleteGame(vector<Game*> &games, string gameName) {
    int i = 0;
    // lock the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLockHandlerDeleteGame);
    int size = games.size();
    for (i; i < size; i++) {
        // if the game's name in the list is equal to the game's name we sent, we will erase it from the list.
        if (games.at(i)->getName().compare(gameName) == 0) {
            games.erase(games.begin() + i);
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerDeleteGame);
}

void Handler::deleteThread(vector<pthread_t *> &threads, pthread_t pthread) {
    int i = 0;
    // lock the vector of threads to prevent changes.
    pthread_mutex_lock(&gamesLockHandlerDeleteThread);
    int size = threads.size();
    for (i; i < size; i++) {
        // if the thread in the list is equal to the thread we sent, we will erase it from the list.
        if (*threads.at(i) == pthread) {
            threads.erase(threads.begin() + i);
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLockHandlerDeleteThread);
}

void Handler::printThreadAndGamesVectorSize() {
    cout << "threads: ";
    //pthread_mutex_lock(&gamesLockHander);
    cout << threadVector.size() << endl;
    //pthread_mutex_unlock(&gamesLockHander);
    cout << "games: ";
    //pthread_mutex_lock(&gamesLockHander);
    cout << games.size() << endl;
    //pthread_mutex_unlock(&gamesLockHander);
}