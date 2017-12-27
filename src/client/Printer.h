// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_PRINTER_H
#define ADVANCEDPROGRAMMING1_PRINTER_H

#include <iostream>
#include "Enum.h"
#include "Point.h"
#include "Board.h"
#include <vector>
using namespace std;

/*
 * in charge of all printing in the game.
 */
class Printer {
public:
    /*
     * function name: printGameOpenning.
     * input: none.
     * output: none.
     * operation: prints the game openning messages.
    */
    virtual void printGameOpenning() = 0;
    /*
     * function name: connectedToServerMessage.
     * input: none.
     * output: none.
     * operation: prints a message that client connected to the server.
    */
    virtual void connectedToServerMessage() = 0;
    /*
     * function name: waitingForConnectionMessage.
     * input: none.
     * output: none.
     * operation: prints a message when waiting for opponent to connect to server.
    */
    virtual void waitingForConnectionMessage() = 0;
    /*
     * function name: failedConnectingToServer.
     * input: none.
     * output: none.
     * operation: prints a message that client failed to connected to the server.
    */
    virtual void failedMessage(const char *msg) = 0;
    /*
     * function name: printInvalidGameMode.
     * input: none.
     * output: none.
     * operation: prints a message that the users game mode choice is invalid.
    */
    virtual void printInvalidGameMode() = 0;
    /*
     * function name: boardSizeMessage.
     * input: none.
     * output: none.
     * operation: print a message asking the user to enter a valid board size.
    */
    virtual void boardSizeMessage() = 0;
    /*
     * function name: waitingMessage.
     * input: none.
     * output: none.
     * operation: prints a message when waiting for opponent.
    */
    virtual void waitingMessage() = 0;
    /*
     * function name: printTurn.
     * input: a char indicating the current player.
     * output: none.
     * operation: prints a message that its a certain player turn.
    */
    virtual void printTurn(type playerType) = 0;
    /*
     * function name: requestMove.
     * input: none.
     * output: none.
     * operation: prints a message asking the player to enter a move.
    */
    virtual void requestMove() = 0;
    /*
     * function name: printPoint.
     * input: the point to print.
     * output: none.
     * operation: prints a given point.
    */
    virtual void printPoint(int* point) = 0;
    /*
     * function name: printBoard.
     * input: the board to print.
     * output: none.
     * operation: prints a given board.
    */
    virtual void printBoard(Board *board) const = 0;
    /*
     * function name: printMove.
     * input: the player who made the move and the x and y values of the move.
     * output: none.
     * operation: print the move the player entered.
    */
    virtual void printMove(type playerType, int x, int y) = 0;
    /*
     * function name: printInvalidMove.
     * input: none.
     * output: none.
     * operation: prints a message indicating the player entered an invalid move.
    */
    virtual void printInvalidMove() = 0;
    /*
     * function name: printPossibleMoves.
     * input: a vector of the players possible moves.
     * output: none.
     * operation: prints all of the points in the vector.
    */
    virtual void printPossibleMoves(vector<Point> possibleMoves) = 0;
    /*
     * function name: printNoMoves.
     * input: none.
     * output: none.
     * operation: prints a message if player has no moves.
    */
    virtual void printNoMoves(type playerType) = 0;
    /*
     * function name: printOpponentHasNoMoves.
     * input: none.
     * output: none.
     * operation: prints a message if opponent has no moves.
    */
    virtual void printOpponentHasNoMoves() = 0;
    /*
     * function name: printWinMessage.
     * input: the player that won.
     * output: none.
     * operation: print a win message according to the player who won.
    */
    virtual void printWinMessage(char winner) = 0;
    virtual void printClientMenu() = 0;
    virtual void gameDeniedMessage(string msg) = 0;
    //virtual void gameNotExist() = 0;
    virtual void gameNotOption() = 0;
    virtual void printGamesList(int sizeOfList, char* list) = 0;
};

#endif //ADVANCEDPROGRAMMING1_PRINTER_H
