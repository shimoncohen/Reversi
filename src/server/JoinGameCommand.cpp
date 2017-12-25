// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    cout << "Entered execute joinGameCommand" << endl;
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
        write(joined->getFirstPlayer(), &startString, STARTMESSAGESIZE*sizeof(char));
        write(joined->getSecondPlayer(), &startString, STARTMESSAGESIZE*sizeof(char));
        cout << "In execute joinGameCommand:\nsent players in game " << joined->getName() << " start message" << endl;
    } else {
        //send not exists
        cout << "In execute joinGameCommand:\nsent NotExist message" << endl;
    }
    // send player nums
}