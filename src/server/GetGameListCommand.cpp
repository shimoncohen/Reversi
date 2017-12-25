//
// Created by shimon on 12/21/17.
//

#include "GetGameListCommand.h"

void GetGameListCommand::execute(vector<string> args, vector<Game*> &games, Game* game, int client) {
    int n, size = 0;
    string list = "";
    const char* send;
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getStatus() == 0) {
            list.append(games[i]->getName());
            list.append("\n");
        }
    }
    size = games.size();
    // sending the size of the list in string display
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
        n = write(client, send, size * sizeof(char));
    } else {
        n = write(client, &NOGAMES, NOGAMESIZE * sizeof(char));
    }
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
         throw "Error, connection disconnected!";
    }
}