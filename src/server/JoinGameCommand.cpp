// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, Game* game, int client) {
    int i = 0;
    Game* joined = NULL;
    for(i; i < games.size(); i++) {
        if(games[i]->getStatus() == 0 && games[i]->getName() == args[0]) {
            games[i]->joinGame(client);
            joined = games[i];
            break;
        }
    }
    string startString = STARTMESSAGE;
    if(joined != NULL) {
        write(joined->getFirstPlayer(), &startString, sizeof(string));
        write(joined->getSecondPlayer(), &startString, sizeof(string));
    } else {
        //send not exists
    }
    // send player nums
}