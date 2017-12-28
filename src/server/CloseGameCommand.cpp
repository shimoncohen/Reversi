//
// Created by shimon on 12/21/17.
//

#include "CloseGameCommand.h"

pthread_mutex_t gamesLockClose;

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games,
                               /*vector<pthread_t*> &threadVector,*/ int client) {
    cout << "Entered execute CloseGameCommand" << endl;
    string closeString = "Close";
    for(int i = 0; i < games.size(); i++) {
        pthread_mutex_lock(&gamesLockClose);
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), &closeString, sizeof(string));
            pthread_mutex_unlock(&gamesLockClose);
            cout << "In execute CloseGameCommand:\nsent Close message to second player" << endl;
            break;
        } else {
            if(games[i]->getSecondPlayer() == client) {
                write(games[i]->getFirstPlayer(), &closeString, sizeof(string));
                cout << "In execute CloseGameCommand:\nsent Close message to first player" << endl;
                pthread_mutex_unlock(&gamesLockClose);
                break;
            }
            pthread_mutex_unlock(&gamesLockClose);
        }
    }
}