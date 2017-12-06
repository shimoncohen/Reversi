// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_SERVERPLAYER_H
#define ADVANCEDPROGRAMMING1_SERVERPLAYER_H

#include "Player.h"
#include "ServerGame.h"

class ServerPlayer : public Player {
public:
    /*
	 * function name: ServerPlayer.
	 * input: the servers IP and port number that the player connects to and the player type.
	 * output: none.
	 * operation: constructor.
	*/
    ServerPlayer(const char *serverIP, int serverPort, type type1);
    /*
	 * function name: connectToServer.
	 * input: none.
	 * output: none.
	 * operation: connects the player to the server.
	*/
    void connectToServer();
    /*
	 * function name: getMove.
	 * input: none.
	 * output: a struct with the opponents move info.
	 * operation: gets the opponents move from the server.
	*/
    struct Info getMove();
    /*
	 * function name: sendMove.
	 * input: the players move.
	 * output: none.
	 * operation: sends the players move to the server.
	*/
    void sendMove(int x, int y);
    type getType();
    int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);
    //for use of HumanPlayer function makeMove(to prevent code duplication)
    friend class HumanPlayer;
private:
    type playerType;
    //the IP of the server the player connects to.
    const char *serverIP;
    //the number of the port the player connects to.
    int serverPort;
    //the client socket number.
    int clientSocket;
};


#endif //ADVANCEDPROGRAMMING1_SERVERPLAYER_H
