// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "MakeMoveCommand.h"

void MakeMoveCommand::execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                              pthread_mutex_t &gamesLock, pthread_mutex_t &threadsLock, ThreadPool& pool, int client) {
    string moveString = "Play " + args[0] + " " + args[1];
    int tempPlayer, i;
    char message[BUFFERSIZE] = {0};
    char feedback[BUFFERSIZE] = {0};
    strcpy(message, moveString.c_str());
    // locking the games vector to prevent changes.
    pthread_mutex_lock(&gamesLock);
    for(i = 0; i < games.size(); i++) {
        // searching for a specific  player socket.
        if(games[i]->getFirstPlayer() == client) {
            tempPlayer = games[i]->getSecondPlayer();
            // writing a move to the player.
            write(tempPlayer, message, BUFFERSIZE*sizeof(char));
            read(tempPlayer, feedback, BUFFERSIZE*sizeof(char));
            if(strcmp(feedback, "again") == 0) {
                write(tempPlayer, message, BUFFERSIZE*sizeof(char));
            }
            break;
        } else if(games[i]->getSecondPlayer() == client) {
            tempPlayer = games[i]->getFirstPlayer();
            // writing a move to the player.
            write(tempPlayer, message, BUFFERSIZE*sizeof(char));
            break;
        }
    }
    // unlock the vector.
    pthread_mutex_unlock(&gamesLock);
}