// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef EX3_AIPLAYER_H
#define EX3_AIPLAYER_H


#include "Player.h"
#include "Board.h"
#include "ConsolePrinter.h"

class AIPlayer : public Player {
private:
    type playerType;
public:
    /*
	 * function name: AIPlayer.
	 * input: type1 - represents the AI players type.
	 * output: none.
     * operation: constructor.
    */
    AIPlayer(type type1);
    /*
	 * function name: ~AIPlayer.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    ~AIPlayer();
    /*
	 * function name: makeMove.
	 * input: the game logic, the current board and the AI's available moves.
	 * output: the best move to play according to the grades.
     * operation: simulates the AI's available moves.
    */
    int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);//will get gameLogic and moves vector
    /*
	 * function name: checkMove.
	 * input: the game logic, the current board and the AI's move.
	 * output: the AI's moves grade according to opponents move.
     * operation: simulates the opponents available moves..
    */
    int checkMove(GameLogic &gameLogic, Board &board, Point point);
    /*
	 * function name: gradeMove.
	 * input: the game logic, the current board and the opponents move.
	 * output: the current boards grade.
     * operation: grades a given board to indicate if the move chosen is preferred.
    */
    int gradeMove(GameLogic &gameLogic, Board &board, Point move);
};


#endif //EX3_AIPLAYER_H
