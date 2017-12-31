// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

pthread_mutex_t lockJoin;

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                              int client) {
    int i = 0, n;
    int secondPlayer;
    Game* joined = NULL;
    // locing the vector of games to prevent changes.
    pthread_mutex_lock(&lockJoin);
    for(i; i < games.size(); i++) {
        // joining the game by ensuring the name is the same, and that the game's status is 0.
        if(games[i]->getStatus() == 0 && games[i]->getName() == args[0]) {
            games[i]->joinGame(client);
            joined = games[i];
            break;
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&lockJoin);
    if(joined != NULL) {
        pthread_t thread;
        // locking the game to prevent changes.
        pthread_mutex_lock(&lockJoin);
        secondPlayer = joined->getSecondPlayer();
        // unlock the game.
        pthread_mutex_unlock(&lockJoin);
        // writing a start message to the second player.
        write(secondPlayer, &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));

        HandleArgs *handleArgs = new HandleArgs();
        // locking the games vector to prevent changes.
        pthread_mutex_lock(&lockJoin);
        handleArgs->games = &games;
        // unlock the vector.
        pthread_mutex_unlock(&lockJoin);
        // locking the games threads to prevent changes.
        pthread_mutex_lock(&lockJoin);
        handleArgs->threadVector = &threadVector;
        // unlock the vector.
        pthread_mutex_unlock(&lockJoin);
        // locking the game to prevent changes.
        pthread_mutex_lock(&lockJoin);
        handleArgs->game = joined;
        // unlock the game.
        pthread_mutex_unlock(&lockJoin);
        handleArgs->socket = client;
        try {
            n = pthread_create(&thread, NULL, Handler::handleGame, (void*)handleArgs);
            // locking the game to prevent changes.
            pthread_mutex_lock(&lockJoin);
            handleArgs->game->setThread(thread);
            // unlock the vector.
            pthread_mutex_unlock(&lockJoin);
            // locking the threads vector to prevent changes.
            pthread_mutex_lock(&lockJoin);
            // inserting the thread to the list
            threadVector.push_back(&thread);
            // unlock the vector.
            pthread_mutex_unlock(&lockJoin);
        } catch (const char* msg) {
            throw msg;
        }
        if (n) {
            cout << "Error: unable to create thread" << endl;
            exit(-1);
        }
    } else {
        // in case the game doesn't exist we sent a proper message.
        write(client, &NOTEXIST, NOTEXISTSIZE*sizeof(char));
    }
}