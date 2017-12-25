// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "MakeMoveCommand.h"

void MakeMoveCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    cout << "Entered execute MakeMoveCommand" << endl;
    string moveString = "Play " + args[0] + " " + args[1];
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getFirstPlayer() == client) {
            write(games[i]->getSecondPlayer(), &moveString, sizeof(string));
            cout << "In execute StartCommand:\nwrote " << moveString << " to second player" << endl;
            break;
        } else if(games[i]->getSecondPlayer() == client) {
            write(games[i]->getFirstPlayer(), &moveString, sizeof(string));
            cout << "In execute StartCommand:\nwrote " << moveString << " to first player" << endl;
            break;
        }
    }
}