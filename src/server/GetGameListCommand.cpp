// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "GetGameListCommand.h"

void GetGameListCommand::execute(vector<string> args, vector<Game*> &games,
                                 vector<pthread_t*> &threadVector,pthread_mutex_t &gamesLock,
                                 pthread_mutex_t &threadsLock, ThreadPool& pool,int client) {
    int n, size = 0;
    string list = "";
    const char* send;
    // locking the vector of the games to prevent changes
    pthread_mutex_lock(&gamesLock);
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getStatus() == 0) {
            // appending the name of waiting games (with status == 0) to the list
            list.append(games[i]->getName());
            // appending end of line after every game name
            list.append("\n");
        }
    }
    // unlock the vector
    pthread_mutex_unlock(&gamesLock);

    size = list.size();
    // sending the size of the list
    n = write(client, &size, sizeof(int));
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "Error, connection disconnected!";
    }
    // sending the list in string display
    if(size != 0) {
        send = list.c_str();
        // sending the the list.
        n = write(client, send, size * sizeof(char));
    } else {
        // in case the list is empty
        n = write(client, &NOGAMES, NOGAMESIZE * sizeof(char));
    }
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "Error, connection disconnected!";
    }
}