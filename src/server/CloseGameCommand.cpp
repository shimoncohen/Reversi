//
// Created by shimon on 12/21/17.
//

#include "CloseGameCommand.h"

pthread_mutex_t gamesLockClose;

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games,
                               /*vector<pthread_t*> &threadVector,*/ int client) {
    //cout << "Entered execute CloseGameCommand" << endl;
    int i;
    for(i = 0; i < games.size(); i++) {
        pthread_mutex_lock(&gamesLockClose);
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), &CLOSE, CLOSESIZE*sizeof(char));
            pthread_mutex_unlock(&gamesLockClose);
            //cout << "In execute CloseGameCommand:\nsent Close message to second player" << endl;
            break;
        } else {
            if(games[i]->getSecondPlayer() == client) {
                write(games[i]->getFirstPlayer(), &CLOSE, CLOSESIZE*sizeof(char));
                //cout << "In execute CloseGameCommand:\nsent Close message to first player" << endl;
                pthread_mutex_unlock(&gamesLockClose);
                break;
            }
            pthread_mutex_unlock(&gamesLockClose);
        }
    }
    i -= 1;
    pthread_mutex_lock(&gamesLockClose);
    games.erase(games.begin() + i);
    pthread_mutex_unlock(&gamesLockClose);
}