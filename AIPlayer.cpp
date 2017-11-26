/*shimon cohen*/
/*315383133*/

#include "AIPlayer.h"

AIPlayer::AIPlayer(type type1) {
    playerType = type1;
}

string* AIPlayer::makeMove(GameLogic &gameLogic, Board *board, vector<Point> &moves) {
    Board *simulator = new Board(*board);
    string *finalDecision = new string[2];
    int i = 0, minGrade = board->getSize() * board->getSize(), currentMinGrade;
    //int *myMove = new int[2];
    for(i; i < moves.size(); i++) {
        currentMinGrade = checkMove(gameLogic, *simulator, moves[i]);
        if(currentMinGrade < minGrade) {
            minGrade = currentMinGrade;
            finalDecision[0] = (int)moves[i].getX();
            finalDecision[1] = (int)moves[i].getY();
        }
    }
//    finalDecition[0] = myMove[0];
//    finalDecition[1] = myMove[1];
    //string a = __STRING(1);
    return finalDecision;
}

int AIPlayer::checkMove(GameLogic &gameLogic, Board &board, Point point) {
    Board *opponentSimulator = new Board(board);
    int i = 0, minGrade = board.getSize() * board.getSize(), currentMinGrade;
    vector<Point> opponentsMoves;
    gameLogic.changeTiles(playerType, point.getX(), point.getY(), *opponentSimulator);
    if(playerType == black) {
        opponentsMoves = gameLogic.availableMoves(board, white);
    } else {
        opponentsMoves = gameLogic.availableMoves(board, black);
    }
    for(i; i < opponentsMoves.size(); i++) {
        currentMinGrade = checkOpponentsMove(gameLogic, board, opponentsMoves[i]);
        if(minGrade > currentMinGrade) {
            minGrade = currentMinGrade;
        }
    }
    return  minGrade;
}

int AIPlayer::checkOpponentsMove(GameLogic &gameLogic, Board &board, Point move) {
    Board *b = new Board(board);
    vector<Point> playerMoves;
    int i = 0, minGrade = board.getSize() * board.getSize(), currentMinGrade;
    if(playerType == black) {
        gameLogic.changeTiles(white, move.getX(), move.getY(), *b);
        playerMoves = gameLogic.availableMoves(*b, black);
    } else if(playerType == white) {
        gameLogic.changeTiles(black, move.getX(), move.getY(), *b);
        playerMoves = gameLogic.availableMoves(*b, white);
    }
    for(i; i < playerMoves.size(); i++) {
        currentMinGrade = gradeMove(gameLogic, *b, playerMoves[i]);
        if(currentMinGrade < minGrade) {
            minGrade = currentMinGrade;
        }
    }
    return minGrade;
}

int AIPlayer::gradeMove(GameLogic &gamLogic, Board &board, Point move) {
    //coping the board
    Board *b = new Board(board);
    int countPlayer = 0, countOther = 0;
    ///making the move on the new board
    gamLogic.changeTiles(playerType, move.getX(), move.getY(), *b);
    //counting the x's and the o's on the board
    for(int i = 0; i < board.getSize(); i++) {
        for(int j = 0; j < board.getSize(); j++) {
            if(playerType == black) {
                if(b->checkCell(i, j) == 'x') {
                    countPlayer++;
                } else if(b->checkCell(i, j) == 'o') {
                    countOther++;
                }
            } else if(playerType == white) {
                if(b->checkCell(i, j) == 'o') {
                    countPlayer++;
                } else if(b->checkCell(i, j) == 'x') {
                    countOther++;
                }
            }
        }
    }
    //giving rate to the move
    return countOther - countPlayer;
}