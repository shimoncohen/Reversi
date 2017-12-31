// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "CloseGameCommand.h"

pthread_mutex_t lockClose;

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games,
                               vector<pthread_t*> &threadVector, int client) {
    int i, tempPlayer;
    // locking the vector of games to prevent changes
    pthread_mutex_lock(&lockClose);
    for(i = 0; i < games.size(); i++) {
        // searching for the current player's socket in the vector
        if (games[i]->getFirstPlayer() == client) {
            tempPlayer = games[i]->getSecondPlayer();
            // unlock the vector
            // sending "close" message to the second player
            write(tempPlayer, &CLOSE, CLOSESIZE * sizeof(char));
            break;
        // in case the socket we search for is the second player
        } else if (games[i]->getSecondPlayer() == client) {
            tempPlayer = games[i]->getFirstPlayer();
            // unlock the vector
            // sending "close" message to the second player
            write(tempPlayer, &CLOSE, CLOSESIZE * sizeof(char));
            break;
        }
    }
    // in case the vector is still locked
//    if(i >= games.size()) {
//        pthread_mutex_unlock(&lockClose);
//    }
    pthread_mutex_unlock(&lockClose);
}