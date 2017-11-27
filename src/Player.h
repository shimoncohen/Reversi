/*shimon cohen*/
/*315383133*/

#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "Enum.h"
#include "GameLogic.h"

/*
 * A player playing the game.
 * An interface (a player may be human or a computer).
 */
class Player {
private:
    type playerType;
public:
    /*
	 * function name:makeMove.
	 * input: none.
	 * output: an array of ints.
     * operation: the player chooses a point on the board to put a piece on (from the available moves he has).
    */
    virtual int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) = 0;
};


#endif //EX1_PLAYER_H
