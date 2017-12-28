// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_GAME_H
#define ADVANCEDPROGRAMMING1_GAME_H

#include <sys/socket.h>
#include <string>

using namespace std;

class Game {
public:
    Game(string gameName, int socket1, int socket2);
    string getName();
    bool getStatus();
    int getFirstPlayer();
    int getSecondPlayer();
    pthread_t getThread();
    void joinGame(int newPlayer);
    void setThread(pthread_t newGameThread);
private:
    string name;
    int firstPlayerSocket;
    int secondPlayerSocket;
    bool status;
    pthread_t gamesThread;
};


#endif //ADVANCEDPROGRAMMING1_GAME_H
