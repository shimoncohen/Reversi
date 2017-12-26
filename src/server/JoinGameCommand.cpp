// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, int client) {
    //cout << "Entered execute joinGameCommand" << endl;
    int i = 0, n;
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
        pthread_t thread;
        firstPlayer = joined->getFirstPlayer();
        secondPlayer = joined->getSecondPlayer();
        //write(joined->getFirstPlayer(), &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));
        write(secondPlayer, &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));
        write(firstPlayer, &playerNum, sizeof(playerNum));
        playerNum = SECOND;
        write(secondPlayer, &playerNum, sizeof(playerNum));

        HandleArgs *handleArgs = new HandleArgs();
        handleArgs->games = &games;
        handleArgs->game = joined;
        handleArgs->socket = client;
        
        try {
                n = pthread_create(&thread, NULL, Handler::handleGame, (void *)handleArgs);
        } catch (const char* msg) {
            throw msg;
        }
        if (n) {
            cout << "Error: unable to create thread" << endl;
            exit(-1);
        }
        //cout << "In execute joinGameCommand:\nsent players in game " << joined->getName() << " start message" << endl;
    } else {
        write(client, &NOTEXIST, NOTEXISTSIZE*sizeof(char));
        //cout << "In execute joinGameCommand:\nsent NotExist message" << endl;
    }
    // send player nums
}