// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_PRINTER_H
#define ADVANCEDPROGRAMMING1_PRINTER_H

#include <iostream>
#include "Enum.h"
#include "Point.h"
#include <vector>
using namespace std;

class Printer {
public:
    virtual void printGameOpenning() = 0;
    virtual void printInvalidGameMode() = 0;
    virtual void boardSizeMessage() = 0;
    virtual void startGameMessage() = 0;
    virtual void printTurn(char type) = 0;
    virtual void requestMove() = 0;
    virtual void printMove(char playerType, int x, int y) = 0;
    virtual void printInvalidMove(char outIn) = 0;
    virtual void printPossibleMoves(vector<Point> possibleMoves) = 0;
    virtual void printWinMessage(char winner) = 0;
};

#endif //ADVANCEDPROGRAMMING1_PRINTER_H
