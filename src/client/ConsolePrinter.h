// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H
#define ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H

#include "Printer.h"

class ConsolePrinter : public Printer {
public:
    void printGameOpenning();
    void connectedToServerMessage();
    void failedConnectingToServer(const char *msg);
    void failedSendingToServer(const char *msg);
    void printInvalidGameMode();
    void boardSizeMessage();
    void startGameMessage();
    void waitingMessage();
    void printTurn(type playerType);
    void requestMove();
    void printMove(type playerType, int x, int y);
    void printPoint(int* point);
    void printBoard(Board *board) const;
    void printInvalidMove(char outIn);
    void printPossibleMoves(vector<Point> possibleMoves);
    void printNoMoves();
    void printOpponentHasNoMoves();
    void printWinMessage(char winner);
};


#endif //ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H
