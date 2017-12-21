// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

void joinGameCommand::execute(vector<string> args, vector<Game> games, int client) {
    int i = 0;
    for(i; i < games.size(); i++) {
        if(games[i].getStatus() == 0 && games[i].getName() == args[0]) {
            ////////////
        }
    }
}