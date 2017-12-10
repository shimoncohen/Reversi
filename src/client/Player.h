// 315383133 shimon cohen
// 302228275 Nadav Spitzer

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
	 * function name: assignType.
	 * input: a type to assign as player type.
	 * output: none.
     * operation: assigns the player the given type.
    */
    virtual void assignType(type playerType1) = 0;
    /*
	 * function name:getType.
	 * input: none.
	 * output: the players type.
     * operation: returns the players type.
    */
    virtual type getType() = 0;
    /*
	 * function name:makeMove.
	 * input: none.
	 * output: an array of ints.
     * operation: the player chooses a point on the board to put a piece on (from the available moves he has).
    */
    virtual int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) = 0;
    /*
	 * function name: recieveOpponentsMove.
	 * input: the players move.
	 * output: none.
	 * operation: gives the opponents move to the player.
	*/
    virtual void recieveOpponentsMove(int x, int y) = 0;
    virtual bool needPrint() = 0;
};


#endif //EX1_PLAYER_H
