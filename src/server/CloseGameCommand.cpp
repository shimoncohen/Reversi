// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "CloseGameCommand.h"

pthread_mutex_t lockClose;

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games,
                               vector<pthread_t*> &threadVector, int client) {
    int i, tempPlayer;
    pthread_mutex_lock(&lockClose);
    for(i = 0; i < games.size(); i++) {
        if (games[i]->getFirstPlayer() == client) {
            tempPlayer = games[i]->getSecondPlayer();
            pthread_mutex_unlock(&lockClose);
            write(tempPlayer, &CLOSE, CLOSESIZE * sizeof(char));
            break;
        } else if (games[i]->getSecondPlayer() == client) {
            tempPlayer = games[i]->getFirstPlayer();
            pthread_mutex_unlock(&lockClose);
            write(tempPlayer, &CLOSE, CLOSESIZE * sizeof(char));
            break;
        }
    }
    if(i >= games.size()) {
        pthread_mutex_unlock(&lockClose);
    }
//    i -= 1;
//    pthread_mutex_lock(&gamesLockClose);
//    games.erase(games.begin() + i);
//    pthread_mutex_unlock(&gamesLockClose);
}