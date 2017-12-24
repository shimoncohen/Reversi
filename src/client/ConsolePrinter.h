// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H
#define ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H

#include "Printer.h"

class ConsolePrinter : public Printer {
public:
    void printGameOpenning();
    void connectedToServerMessage();
    void waitingForConnectionMessage();
    void failedMessage(const char *msg);
    void printInvalidGameMode();
    void boardSizeMessage();
    void waitingMessage();
    void printTurn(type playerType);
    void requestMove();
    void printMove(type playerType, int x, int y);
    void printPoint(int* point);
    void printBoard(Board *board) const;
    void printInvalidMove();
    void printPossibleMoves(vector<Point> possibleMoves);
    void printNoMoves(type playerType);
    void printOpponentHasNoMoves();
    void printWinMessage(char winner);
    void printClientMenu();
    void gameAlreadyExist();
    void gameNotExist();
    void gameNotOption();
    void printGamesList(int sizeOfList, char* list);
};


#endif //ADVANCEDPROGRAMMING1_CONSOLEPRINTER_H
