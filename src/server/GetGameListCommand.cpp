//
// Created by shimon on 12/21/17.
//

#include "GetGameListCommand.h"

void GetGameListCommand::execute(vector<string> args, vector<Game*> games, int client) {
    int n, size = 0;
    string list = "";
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getStatus() == 0) {
            list.append(games[i]->getName());
            list.append("\n");
        }
    }
    size = list.size();
    // sending the size of the list in string display
    n = write(client, &size, sizeof(int));
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "Error, connection disconnected!";
    }
    // sending the list in string display
    n = write(client, list.c_str(), size * sizeof(char));
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
         throw "Error, connection disconnected!";
    }
}