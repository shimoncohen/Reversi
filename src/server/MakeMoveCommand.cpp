// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "MakeMoveCommand.h"

void MakeMoveCommand::execute(vector<string> args, int client) {
    string moveString = "Play " + args[0] + " " + args[1];
    write(client, &moveString, sizeof(string));
}
