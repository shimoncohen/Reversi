// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StartCommand.h"

void StartCommand::execute(vector<string> args, vector<Game*> games, int client) {
    Game* newGame = NULL;
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getName().compare(args[0]) != 0) {
            newGame = games[i];
        }
    }
    if(newGame == NULL) {
        write(client, &EXISTS, EXISTSIZE * sizeof(char));
        return;
    }
    newGame = new Game(args[0], client, 0);////segmentation fault
    games.push_back(newGame);
}