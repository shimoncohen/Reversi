// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef EX1_STANDARTGAMELOGIC_H
#define EX1_STANDARTGAMELOGIC_H


#include "GameLogic.h"

/*
 * The class decides the game logic of a regular game of reversi.
 * The standart rules apply.
 */
class StandartGameLogic : public GameLogic {
public:
    void changeTiles(type type, int x, int y, Board &board);
    vector<Point> availableMoves(Board &board, type type1);
private:
    bool validMove(Board &board, int x, int y, int right, int down, char piece, int iteration);
    void flipTiles(char type, int x, int y, int right, int down, Board &board);
};


#endif //EX1_STANDARTGAMELOGIC_H