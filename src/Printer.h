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
    /*
     * function name: printGameOpenning.
     * input: none.
     * output: none.
     * operation: prints the game openning messages.
    */
    virtual void printGameOpenning() = 0;
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
     * function name: startGameMessage.
     * input: none.
     * output: none.
     * operation: prints a start game message.
    */
    virtual void startGameMessage() = 0;
    /*
     * function name: printTurn.
     * input: a char indicating the current player.
     * output: none.
     * operation: prints a message that its a certain player turn.
    */
    virtual void printTurn(char type) = 0;
    /*
     * function name: requestMove.
     * input: none.
     * output: none.
     * operation: prints a message asking the player to enter a move.
    */
    virtual void requestMove() = 0;
    /*
     * function name: printMove.
     * input: the player who made the move and the x and y values of the move.
     * output: none.
     * operation: print the move the player entered.
    */
    virtual void printMove(char playerType, int x, int y) = 0;
    /*
     * function name: printInvalidMove.
     * input: none.
     * output: none.
     * operation: prints a message indicating the player entered an invalid move.
    */
    virtual void printInvalidMove(char outIn) = 0;
    /*
     * function name: printPossibleMoves.
     * input: a vector of the players possible moves.
     * output: none.
     * operation: prints all of the points in the vector.
    */
    virtual void printPossibleMoves(vector<Point> possibleMoves) = 0;
    /*
     * function name: printWinMessage.
     * input: the player that won.
     * output: none.
     * operation: print a win message according to the player who won.
    */
    virtual void printWinMessage(char winner) = 0;
};

#endif //ADVANCEDPROGRAMMING1_PRINTER_H
