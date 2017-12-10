// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef EX1_LOCALGAME_H
#define EX1_LOCALGAME_H

#include "GameLogic.h"
#include "Player.h"
#include "StandartGameLogic.h"
#include "Point.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Board.h"
#include "ConsolePrinter.h"
#include "Game.h"
#include "ServerPlayer.h"

typedef struct Info {
    int x;
    int y;
}Info;

/*
 * A game played.
 * manages the game itself, like the players turns and acts acoording to the game logic given to it.
 */
class Game{
private:
    GameLogic* gameLogic;//the logic the game plays by.
    Board* board;//the game board.
    Player* firstPlayer;//the first player in the game.
    Player* secondPlayer;// the second player in the game.
public:
    /*
	 * function name: Game.
	 * input: the boards size, the gameLogic the game should play by, and the two players.
	 * output: none.
     * operation: constructor.
    */
    Game(int boardSize, GameLogic* newGameLogic, Player* first, Player* second);
    /*
	 * function name: Game.
	 * input: the gameLogic the game should play by, and the two players.
	 * output: none.
     * operation: constructor.
    */
    Game(GameLogic* newGameLogic, Player* first, Player* second);
    /*
	 * function name: Game input: none.
	 * output: none.
     * operation: deconstructor.
    */
    ~Game();
    /*
	 * function name: assignTypes.
	 * input: none.
	 * output: none.
     * operation: assigns playerTypes to the players.
    */
    void assignTypes();
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


#endif //EX1_LOCALGAME_H
