// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H
#define ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H

#include "Printer.h"

class ConsolePrinter : public Printer {
public:
    void printGameOpenning();
    void printInvalidGameMode();
    void boardSizeMessage();
    void startGameMessage();
    void printTurn(char type);
    void requestMove();
    void printMove(char playerType, int x, int y);
    void printInvalidMove(char outIn);
    void printPossibleMoves(vector<Point> possibleMoves);
    void printWinMessage(char winner);
};


#endif //ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H
