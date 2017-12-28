// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "JoinGameCommand.h"

pthread_mutex_t lockJoin;

void joinGameCommand::execute(vector<string> args, vector<Game*> &games, vector<pthread_t*> &threadVector,
                              int client) {
    //cout << "Entered execute joinGameCommand" << endl;
    int i = 0, n;
    int secondPlayer;
    Game* joined = NULL;
    pthread_mutex_lock(&lockJoin);
    for(i; i < games.size(); i++) {
        if(games[i]->getStatus() == 0 && games[i]->getName() == args[0]) {
            games[i]->joinGame(client);
            joined = games[i];
            break;
        }
    }
    pthread_mutex_unlock(&lockJoin);
    if(joined != NULL) {
        pthread_t thread;
        pthread_mutex_lock(&lockJoin);
        secondPlayer = joined->getSecondPlayer();
        pthread_mutex_unlock(&lockJoin);
        write(secondPlayer, &STARTMESSAGE, STARTMESSAGESIZE*sizeof(char));

        HandleArgs *handleArgs = new HandleArgs();

        pthread_mutex_lock(&lockJoin);
        handleArgs->games = &games;
        pthread_mutex_unlock(&lockJoin);
        pthread_mutex_lock(&lockJoin);
        handleArgs->threadVector = &threadVector;
        pthread_mutex_unlock(&lockJoin);
        pthread_mutex_lock(&lockJoin);
        handleArgs->game = joined;
        pthread_mutex_unlock(&lockJoin);
        handleArgs->socket = client;

        try {
            n = pthread_create(&thread, NULL, Handler::handleGame, (void*)handleArgs);
            pthread_mutex_lock(&lockJoin);
            handleArgs->game->setThread(thread);
            pthread_mutex_unlock(&lockJoin);
            pthread_mutex_lock(&lockJoin);
            threadVector.push_back(&thread);
            pthread_mutex_unlock(&lockJoin);
            // inserting the thread to the list
            /*pthread_mutex_lock(&list_mutex);
            threadVector.push_back(&thread);
            pthread_mutex_unlock(&list_mutex);*/
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