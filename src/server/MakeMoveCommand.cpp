// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "MakeMoveCommand.h"

pthread_mutex_t gamesLockMove;

void MakeMoveCommand::execute(vector<string> args, vector<Game*> &games,
                              vector<pthread_t*> &threadVector, int client) {
    //cout << "Entered execute MakeMoveCommand" << endl;
    string moveString = "Play " + args[0] + " " + args[1];
    int tempPlayer, i;
    const char *message = moveString.c_str();
    pthread_mutex_lock(&gamesLockMove);
    for(i = 0; i < games.size(); i++) {
        if(games[i]->getFirstPlayer() == client) {
            tempPlayer = games[i]->getSecondPlayer();
            pthread_mutex_unlock(&gamesLockMove);
            write(tempPlayer, message, BUFFERSIZE*sizeof(char));
            //cout << "In execute StartCommand:\nwrote " << moveString << " to second player" << endl;
            break;
        } else if(games[i]->getSecondPlayer() == client) {
            tempPlayer = games[i]->getFirstPlayer();
            pthread_mutex_unlock(&gamesLockMove);
            write(tempPlayer, message, BUFFERSIZE*sizeof(char));
            //cout << "In execute StartCommand:\nwrote " << moveString << " to first player" << endl;
            break;
        }
    }
    if(i >= games.size()) {
        pthread_mutex_unlock(&gamesLockMove);
    }
}