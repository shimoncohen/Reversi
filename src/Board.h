/*shimon cohen*/
/*315383133*/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
using namespace std;

enum boardChar {black, white, space};

/*
 * The game board.
 * an interface for board objects.
 */
class Board {
private:
	boardChar** board;
	int boardSize;
public:
	/*
	 * function name: getSize.
	 * input: none.
	 * output: the size of the board.
     * operation: returns the boards size.
    */
	virtual int getSize() = 0;
	/*
	 * function name: checkCell.
	 * input: x and y values (row and column).
	 * output: the char in the cell.
     * operation: returnes the char in a given cell.
    */
	virtual char checkCell(const int x, const int y) = 0;
	/*
	 * function name: putTile.
	 * input: x and y values of a cell and a type to put in the cell.
	 * output: none.
     * operation: puts a players piece in a given cell of the board.
    */
	virtual void putTile(const int x, const int y, const char type) = 0;
    /*
	 * function name: operator <<.
	 * input: a stream and a board object.
	 * output: a stream we write the board in to.
     * operation: prints the board in to a stream and returnes it overriding the << operator.
    */
	friend ostream &operator <<(ostream &out, Board &board1);
    /*
	 * function name: operator ==.
	 * input: two board object.
	 * output: a boolean value indicating if boards are equal.
     * operation: returns 1 if boards are equal, 0 otherwise.
    */
    friend bool operator ==(Board &board1, Board &board2);
};
#endif