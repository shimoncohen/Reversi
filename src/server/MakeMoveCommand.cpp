// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "MakeMoveCommand.h"

pthread_mutex_t gamesLockMove;

void MakeMoveCommand::execute(vector<string> args, vector<Game*> &games,
                              vector<pthread_t*> &threadVector, int client) {
    //cout << "Entered execute MakeMoveCommand" << endl;
    string moveString = "Play " + args[0] + " " + args[1];
    const char *message = moveString.c_str();
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), message, BUFFERSIZE*sizeof(char));
            //cout << "In execute StartCommand:\nwrote " << moveString << " to second player" << endl;
            pthread_mutex_unlock(&gamesLockMove);
            break;
        } else if(games[i]->getSecondPlayer() == client) {
            write(games[i]->getFirstPlayer(), message, BUFFERSIZE*sizeof(char));
            //cout << "In execute StartCommand:\nwrote " << moveString << " to first player" << endl;
            pthread_mutex_unlock(&gamesLockMove);
            break;
        }
    }
    pthread_mutex_unlock(&gamesLockMove);
}