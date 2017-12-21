// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StartCommand.h"

void StartCommand::execute(vector<string> args, vector<Game> games, int client) {
    string startString = STARTMESSAGE;
    write(client, &startString, sizeof(string));
}