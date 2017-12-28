//
// Created by shimon on 12/21/17.
//

#include "CloseGameCommand.h"

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games,
                               /*vector<pthread_t*> &threadVector,*/ int client) {
    pthread_mutex_t gamesLock;
    cout << "Entered execute CloseGameCommand" << endl;
    string closeString = "Close";
    for(int i = 0; i < games.size(); i++) {
        pthread_mutex_lock(&gamesLock);
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), &closeString, sizeof(string));
            pthread_mutex_unlock(&gamesLock);
            cout << "In execute CloseGameCommand:\nsent Close message to second player" << endl;
            break;
        } else {
            if(games[i]->getSecondPlayer() == client) {
                write(games[i]->getFirstPlayer(), &closeString, sizeof(string));
                cout << "In execute CloseGameCommand:\nsent Close message to first player" << endl;
                pthread_mutex_unlock(&gamesLock);
                break;
            }
            pthread_mutex_unlock(&gamesLock);
        }
    }
}