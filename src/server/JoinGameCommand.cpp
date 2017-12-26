// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    //cout << "Entered execute joinGameCommand" << endl;
    int i = 0;
    int playerNum = FIRST, firstPlayer, secondPlayer;
    Game* joined = NULL;
    for(i; i < games.size(); i++) {
        if(games[i]->getStatus() == 0 && games[i]->getName() == args[0]) {
            games[i]->joinGame(client);
            joined = games[i];
            break;
        }
    }
    if(joined != NULL) {
        firstPlayer = joined->getFirstPlayer();
        secondPlayer = joined->getSecondPlayer();
        //write(joined->getFirstPlayer(), &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));
        write(secondPlayer, &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));
        write(firstPlayer, &playerNum, sizeof(playerNum));
        playerNum = SECOND;
        write(secondPlayer, &playerNum, sizeof(playerNum));
        //cout << "In execute joinGameCommand:\nsent players in game " << joined->getName() << " start message" << endl;
    } else {
        write(client, &NOTEXIST, NOTEXISTSIZE*sizeof(char));
        //cout << "In execute joinGameCommand:\nsent NotExist message" << endl;
    }
    // send player nums
}