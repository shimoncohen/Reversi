//
// Created by shimon on 12/21/17.
//

#include "CloseGameCommand.h"

void CloseGameCommand::execute(vector<string> args, vector<Game*> games, int client) {
    string closeString = "Close";
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), &closeString, sizeof(string));
            break;
        } else if(games[i]->getSecondPlayer() == client) {
            write(games[i]->getFirstPlayer(), &closeString, sizeof(string));
            break;
        }
    }
}