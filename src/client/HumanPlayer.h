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
	 * input: none.
	 * output: none.
     * operation: constructor.
    */
    HumanPlayer();
    /*
	 * function name: ~HumanPlayer.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    ~HumanPlayer();
    void assignType(type playerType1);
    type getType();
    int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);
    void recieveOpponentsMove(int x, int y);
    bool needPrint();
};


#endif //EX1_HUMANPLAYER_H
