// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                               pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, ThreadPool& pool, int client) {
    int i = 0;
    //int n;
    int secondPlayer;
    Game* joined = NULL;
    // locking the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLock);
    for(i; i < games.size(); i++) {
        // joining the game by ensuring the name is the same, and that the game's status is 0.
        if(games[i]->getStatus() == 0 && games[i]->getName() == args[0]) {
            games[i]->joinGame(client);
            joined = games[i];
            break;
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLock);
    if(joined != NULL) {
        // locking the game to prevent changes.
        pthread_mutex_lock(&gamesLock);
        secondPlayer = joined->getSecondPlayer();
        // unlock the game.
        pthread_mutex_unlock(&gamesLock);
        // writing a start message to the second player.
        write(secondPlayer, &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));

        HandleArgs *handleArgs = new HandleArgs();
        // locking the games vector to prevent changes.
        handleArgs->threadsLock = &threadsLock;
        handleArgs->gamesLock = &gamesLock;
        pthread_mutex_lock(&gamesLock);
        handleArgs->games = &games;
        // unlock the vector.
        pthread_mutex_unlock(&gamesLock);
        // locking the games threads to prevent changes.
        pthread_mutex_lock(&threadsLock);
        handleArgs->threadVector = &threadVector;
        // unlock the vector.
        pthread_mutex_unlock(&threadsLock);
        // locking the game to prevent changes.
        pthread_mutex_lock(&gamesLock);
        handleArgs->game = joined;
        // unlock the game.
        pthread_mutex_unlock(&gamesLock);
        handleArgs->socket = client;
        try {
            pool.addTask(new Task(Handler::handleGame, (void*)handleArgs));
            // locking the game to prevent changes.
            pthread_mutex_lock(&gamesLock);
            // unlock the vector.
            pthread_mutex_unlock(&gamesLock);
            // locking the threads vector to prevent changes.
            pthread_mutex_lock(&threadsLock);
            // unlock the vector.
            pthread_mutex_unlock(&threadsLock);
        } catch (const char* msg) {
            throw msg;
        }
    } else {
        // in case the game doesn't exist we sent a proper message.
        write(client, &NOTEXIST, NOTEXISTSIZE*sizeof(char));
    }
}