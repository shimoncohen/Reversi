// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StartCommand.h"

pthread_mutex_t gamesLockStart;

void StartCommand::execute(vector<string> args, vector<Game*> &games, /*vector<pthread_t*> &threadVector,*/ int client) {
    //cout << "Entered execute StartCommand\n" << endl;
    Game* newGame = NULL;
    pthread_mutex_lock(&gamesLockStart);
    for(int i = 0; i < games.size(); i++) {
        if(games[i]->getName().compare(args[0]) == 0) {
            newGame = games[i];
        }
    }
    pthread_mutex_unlock(&gamesLockStart);
    if(newGame != NULL) {
        write(client, &EXISTS, EXISTSIZE * sizeof(char));
        //cout << "In execute StartCommand:\nwrote AlreadyExist message\n" << endl;
        return;
    }
    write(client, &DOSENTEXIST, DOSENTEXISTSIZE * sizeof(char));
    //cout << "In execute StartCommand:\nwrote DoesNotExist message\n" << endl;
    newGame = new Game(args[0], client, 0);
    pthread_mutex_lock(&gamesLockStart);
    games.push_back(newGame);
    pthread_mutex_unlock(&gamesLockStart);
    //cout << "In execute StartCommand:\nadded new game to list by name " << newGame->getName() << endl << endl;
}