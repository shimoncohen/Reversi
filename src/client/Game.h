// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_GAME_H
#define ADVANCEDPROGRAMMING1_GAME_H

#include "GameLogic.h"
#include "Player.h"
#include "StandartGameLogic.h"
#include "Point.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Board.h"
#include "ConsolePrinter.h"

/*
 * A game played.
 * manages the game itself, like the players turns and acts acoording to the game logic given to it.
 */
class Game {
private:
    GameLogic* gameLogic;//the logic the game plays by.
    Board* board;//the game board.
    Player* firstPlayer;//the first player in the game.
    Player* secondPlayer;// the second player in the game.
    int turn;
public:
    /*
	 * function name: runGame.
	 * input: none.
	 * output: none.
     * operation: runs the game.
    */
    virtual void runGame() = 0;
    /*
	 * function name: doOneTurn.
	 * input: a vector of the current player valid moves.
	 * output: none.
     * operation: runs a whole turn.
     *            runs a players turn.
    */
    virtual void doOneTurn(vector<Point> v) = 0;
};

#endif //ADVANCEDPROGRAMMING1_GAME_H