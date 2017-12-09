// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef EX1_GAMELOGIC_H
#define EX1_GAMELOGIC_H

#include <string>
#include <vector>
#include "Board.h"
#include "Enum.h"
#include "Point.h"
using namespace std;

/*
 * An abstract class.
 * Decides the logic of the game played.
 */
class GameLogic {
public:
    /*
	 * function name: availableMoves.
	 * input: type- the player type(black/white). board- the game board.
	 * output: a vector of points indicating the available moves.
     * operation: searches the board for available moves for the current player.
    */
    virtual vector<Point> availableMoves(Board &board, type type1) = 0;
    /*
	 * function name: validOption.
	 * input: the players move.
	 * output: true if optional move, false otherwise.
     * operation: checks if the move is an optional move and returns true if it is, false otherwise.
    */
    virtual bool validOption(Board &board, int x, int y, vector<Point> options) = 0;
    /*
	 * function name: changeTiles.
	 * input: type- the player type(black/white). x- the row. y- the column. board- the game board.
	 * output: none.
	 * operation: changes the tiles on the board according to the game logic.
	*/
    virtual void changeTiles(type type, int x, int y, Board &board) = 0;
    /*
	 * function name: gameWon.
	 * input: none.
	 * output: the playerType of the player who won, otherwise t for tie.
     * operation: returns the winning player's type, otherwise returns t for tie.
    */
    virtual char gameWon(Board &board) = 0;
    /*
	 * function name: isGameWon.
	 * input: none.
	 * output: true if board is full, false otherwise.
     * operation: returns true if board is full, false otherwise.
    */
    virtual bool isGameWon(Board &board) = 0;
    /*
	 * function name: gameFinalMove.
	 * input: the game board and the last move.
	 * output: true if the game ends after given move, false otherwise.
     * operation: plays give move on board and returns true if the given move was the final move, false otherwise.
    */
    virtual bool gameFinalMove(Board &board, type pType, int x, int y) = 0;
private:
    /*
	 * function name: validMove.
	 * input: a board object, x and y values for a move, right and down to check the vector for valid move
     *        piece to know what pieces to look for, and iteration to know the amount of pieces turned.
	 * output: 1 if valid move, else 0.
     * operation: checks a vector from a certain point for a valid move.
    */
    virtual bool validMove(Board &board, int x, int y, int right, int down, char piece, int iteration) = 0;
    /*
	 * function name: flipTiles.
	 * input: the players type, x and y values to know where to start flipping from, right and down to know the
     *        vectors direction, and the board.
	 * output: none.
     * operation: flips all of the tiles in the vectors way that are valid moves.
    */
    virtual void flipTiles(char type, int x, int y, int right, int down, Board &board) = 0;
};


#endif //EX1_GAMELOGIC_H
