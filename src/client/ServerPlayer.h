// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_SERVERPLAYER_H
#define ADVANCEDPROGRAMMING1_SERVERPLAYER_H

#include "Player.h"
#include "ServerGame.h"

class ServerPlayer : public Player {
public:
    ServerPlayer(const char *serverIP, int serverPort, type type1);
    void connectToServer();
    info getMove();
    void sendMove(Board &board, int x, int y);
    int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);
private:
    type playerType;
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //ADVANCEDPROGRAMMING1_SERVERPLAYER_H
