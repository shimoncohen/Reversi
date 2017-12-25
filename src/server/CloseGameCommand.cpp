//
// Created by shimon on 12/21/17.
//

#include "CloseGameCommand.h"

void CloseGameCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    cout << "Entered execute CloseGameCommand" << endl;
    string closeString = "Close";
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), &closeString, sizeof(string));
            cout << "In execute CloseGameCommand:\nsent Close message to second player" << endl;
            break;
        } else if(games[i]->getSecondPlayer() == client) {
            write(games[i]->getFirstPlayer(), &closeString, sizeof(string));
            cout << "In execute CloseGameCommand:\nsent Close message to first player" << endl;
            break;
        }
    }
}