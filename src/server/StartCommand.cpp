// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StartCommand.h"

void StartCommand::execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                           pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, int client) {
    Game* newGame = NULL;
    // locking the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLock);
    for(int i = 0; i < games.size(); i++) {
        // checking if the game exists.
        if(games[i]->getName().compare(args[0]) == 0) {
            newGame = games[i];
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLock);
    if(newGame != NULL) {
        // in case the game already exists.
        write(client, &EXISTS, EXISTSIZE * sizeof(char));
        return;
    }
    // in case the game doesn't exist we create a new one and add it to the games list.
    write(client, &DOSENTEXIST, DOSENTEXISTSIZE * sizeof(char));
    newGame = new Game(args[0], client, 0);
    // locking the vector of games to prevent changes.
    pthread_mutex_lock(&gamesLock);
    games.push_back(newGame);
    // unlock the vector.
    pthread_mutex_unlock(&gamesLock);
}