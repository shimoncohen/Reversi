// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StartCommand.h"

void StartCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    cout << "Entered execute StartCommand\n" << endl;
    Game* newGame = NULL;
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getName().compare(args[0]) == 0) {
            newGame = games[i];
        }
    }
    if(newGame != NULL) {
        write(client, &EXISTS, EXISTSIZE * sizeof(char));
        cout << "In execute StartCommand:\nwrote AlreadyExist message\n" << endl;
        return;
    }
    write(client, &DOSENTEXIST, DOSENTEXISTSIZE * sizeof(char));
    cout << "In execute StartCommand:\nwrote DoesNotExist message\n" << endl;
    newGame = new Game(args[0], client, 0);
    games.push_back(newGame);
    cout << "In execute StartCommand:\nadded new game to list by name " << newGame->getName() << endl << endl;
}