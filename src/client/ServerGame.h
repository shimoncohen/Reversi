//
// Created by shimon on 12/3/17.
//

#ifndef ADVANCEDPROGRAMMING1_SERVERGAME_H
#define ADVANCEDPROGRAMMING1_SERVERGAME_H

#include "LocalGame.h"
#include "ServerPlayer.h"

typedef struct {
    Board *board;
    int x;
    int y;
}info;

class ServerGame : public Game {
private:
    GameLogic* gameLogic;//the logic the game plays by.
    Board* board;//the game board.
    Player* firstPlayer;//the first player in the game.
    Player* secondPlayer;// the second player in the game.
    int turn;
public:
    /*
	 * function name: ServerGame.
	 * input: the boards size, the gameLogic the game should play by, and the two players.
	 * output: none.
     * operation: constructor.
    */
    ServerGame(int boardSize, GameLogic* newGameLogic, Player* first, Player* second);
    /*
	 * function name: ~ServerGame.
	 * input: none.
	 * output: none.
     * operation: deconstructor.
    */
    ~ServerGame();
    /*
	 * function name: runGame.
	 * input: none.
	 * output: none.
     * operation: runs the game.
    */
    void runGame();
    /*
	 * function name: doOneTurn.
	 * input: a vector of the current player valid moves.
	 * output: none.
     * operation: runs a whole turn.
     *            runs a players turn.
    */
    void doOneTurn(vector<Point> v);
};


#endif //ADVANCEDPROGRAMMING1_SERVERGAME_H
