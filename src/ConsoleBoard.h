/*shimon cohen*/
/*315383133*/

#ifndef CONSOLEBOARD_H
#define CONSOLEBOARD_H

#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

/*
 * The console game board.
 * holdes and manages the board.
 */
class ConsoleBoard : public Board {
private:
    boardChar** board;
    int boardSize;
public:
    /*
     * function name: Board.
     * input: none.
     * output: none.
     * operation: constructor. initializes the board.
    */
    ConsoleBoard(int size);
    /*
     * function name: Board.
     * input: board.
     * output: none.
     * operation: constructor. initializes the board from a different board object.
    */
    ConsoleBoard(Board &board1);
    /*
     * function name: ~Board.
     * input: none.
     * output: none.
     * operation: deconstructor.
    */
    ~ConsoleBoard();
    /*
     * function name: print.
     * input: none.
     * output: none.
     * operation: prints the current board state.
    */
    void print();
    /*
     * function name: getSize.
     * input: none.
     * output: the size of the board.
     * operation: returns the boards size.
    */
    int getSize();
    /*
     * function name: checkCell.
     * input: x and y values (row and column).
     * output: the char in the cell.
     * operation: returnes the char in a given cell.
    */
    char checkCell(const int x, const int y);
    /*
     * function name: putTile.
     * input: x and y values of a cell and a type to put in the cell.
     * output: none.
     * operation: puts a players piece in a given cell of the board.
    */
    void putTile(const int x, const int y, const char type);
    /*
	 * function name: operator <<.
	 * input: a stream and a board object.
	 * output: a stream we write the board in to.
     * operation: prints the board in to a stream and returnes it overriding the << operator.
    */
    friend ostream &operator <<(ostream &out, ConsoleBoard &board1);
    /*
	 * function name: operator ==.
	 * input: a board object.
	 * output: a boolean value indicating if boards are equal.
     * operation: returns 1 if boards are equal, 0 otherwise.
    */
    friend bool operator ==(ConsoleBoard &board1, ConsoleBoard &board2);
};
#endif //CONSOLEBOARD_H
