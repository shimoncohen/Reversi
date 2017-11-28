/*shimon cohen*/
/*315383133*/

#ifndef EX3_AIPLAYER_H
#define EX3_AIPLAYER_H


#include "Player.h"
#include "Board.h"

class AIPlayer : public Player {
private:
    type playerType;
public:
    AIPlayer(type type1);
    ~AIPlayer();
    int* makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves);//will get gameLogic and moves vector
    int checkMove(GameLogic &gameLogic, Board &board, Point point);
    int checkOpponentsMove(GameLogic &gameLogic, Board &board, Point move);
    int gradeMove(GameLogic &gameLogic, Board &board, Point move);
};


#endif //EX3_AIPLAYER_H
