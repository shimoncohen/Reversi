// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StartCommand.h"

void StartCommand::execute(vector<string> args, vector<Game*> games, int client) {
    Game *newGame = new Game(args[0], client, 0);////segmentation fault
    games.push_back(newGame);
}