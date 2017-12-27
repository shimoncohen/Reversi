// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "GetGameListCommand.h"

void GetGameListCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    //cout << "Entered execute GetGameListCommand" << endl;
    int n, size = 0;
    string list = "";
    const char* send;
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getStatus() == 0) {
            list.append(games[i]->getName());
            list.append("\n");
        }
    }
    size = list.size();
    // sending the size of the list in string display
    n = write(client, &size, sizeof(int));
    //cout << "In execute GetGameListCommand:\nwrote size of string " << size << endl;
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
        //cout << "In execute GetGameListCommand:\nwrote message: " << send << endl;
    } else {
        n = write(client, &NOGAMES, NOGAMESIZE * sizeof(char));
        //cout << "In execute GetGameListCommand:\nwrote no available games" << size << endl;
    }
    if (n == -1) {
        throw "Error writing command to socket";
    }
    if (n == 0) {
        throw "Error, connection disconnected!";
    }
}