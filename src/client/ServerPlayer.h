// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_SERVERPLAYER_H
#define ADVANCEDPROGRAMMING1_SERVERPLAYER_H

#include "Player.h"
#include "Game.h"
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 200
#define TWO 2

class ServerPlayer : public Player {
public:
    /*
	 * function name: ServerPlayer.
	 * input: the servers IP and port number that the player connects to.
	 * output: none.
	 * operation: constructor.
	*/
    ServerPlayer(const char *serverIP, int serverPort);
    //TODO change comments
    /*
	 * function name: connectToServer.
	 * input: none.
	 * output: none.
	 * operation: connects the player to the server.
	*/
    void connectToServer();
    void startGame();
    /*
	 * function name: getMove.
	 * input: none.
	 * output: a struct with the opponents move info.
	 * operation: gets the opponents move from the server.
	*/
    struct Info getMove();
    void assignType(type playerType1);
    type getType();
    int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);
    /*
	 * function name: recieveOpponentsMove.
	 * input: the players move.
	 * output: none.
	 * operation: sends the players move to the server.
	*/
    void recieveOpponentsMove(int x, int y);
    bool needPrint();
    void clientMenu();
    string translateOperation(int oper, string &name);
private:
    type playerType;
    //the IP of the server the player connects to.
    const char *serverIP;
    //the number of the port the player connects to.
    int serverPort;
    //the client socket number.
    int clientSocket;
    //string gameName;
    Info extractCommandAndArgs(char* buffer);
    void reconnect();
};


#endif //ADVANCEDPROGRAMMING1_SERVERPLAYER_H
