// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef EX1_HUMANPLAYER_H
#define EX1_HUMANPLAYER_H

#include <iostream>
#include "Player.h"
using namespace std;

/*
 * A humanPlayer from type Player.
 * represents a human player.
 */
class HumanPlayer : public Player {
private:
    type playerType;
public:
    /*
	 * function name: HumanPlayer.
	 * input: type1 - represents the players type.
	 * output: none.
     * operation: constructor.
    */
    HumanPlayer(type type1);
    /*
	 * function name: ~HumanPlayer.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    ~HumanPlayer();
    virtual int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);
};


#endif //EX1_HUMANPLAYER_H
