/*shimon cohen*/
/*315383133*/

#include "AIPlayer.h"

AIPlayer::AIPlayer(type type1) {
    playerType = type1;
}

AIPlayer::~AIPlayer() {

}

int* AIPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    Board *simulator = new Board(board);
    int i = 0, minGrade = simulator->getSize() * simulator->getSize(), currentMinGrade;
    int *myMove = new int[2];
    for(i; i < moves.size(); i++) {
        currentMinGrade = checkMove(gameLogic, *simulator, moves[i]);
        if(currentMinGrade < minGrade) {
            minGrade = currentMinGrade;
            myMove[0] = moves[i].getX();
            myMove[1] = moves[i].getY();
        }
    }
    delete simulator;
    return myMove;
}

int AIPlayer::checkMove(GameLogic &gameLogic, Board &board, Point point) {
    Board *opponentSimulator = new Board(board);
    int minGrade = opponentSimulator->getSize() * opponentSimulator->getSize(), currentMinGrade;
    vector<Point> opponentsMoves;
    gameLogic.changeTiles(playerType, point.getX(), point.getY(), *opponentSimulator);
    if(playerType == blackPlayer) {
        opponentsMoves = gameLogic.availableMoves(*opponentSimulator, whitePlayer);
    } else {
        opponentsMoves = gameLogic.availableMoves(*opponentSimulator, blackPlayer);
    }
    if(opponentsMoves.size() == 0) {
        delete opponentSimulator;
        return -1;
    }
    for(int i = 0; i < opponentsMoves.size(); i++) {
        currentMinGrade = gradeMove(gameLogic, board, opponentsMoves[i]);
        if(minGrade > currentMinGrade) {
            minGrade = currentMinGrade;
        }
    }
    delete opponentSimulator;
    return minGrade;
}

int AIPlayer::gradeMove(GameLogic &gameLogic, Board &board, Point move) {
    //coping the board
    Board *tempBoard = new Board(board);
    int countPlayer = 0, countOther = 0;
    ///making the move on the new board
    gameLogic.changeTiles(playerType, move.getX(), move.getY(), *tempBoard);
    //counting the x's and the o's on the board
    for(int i = 0; i < tempBoard->getSize(); i++) {
        for(int j = 0; j < tempBoard->getSize(); j++) {
            if(playerType == blackPlayer) {
                if(tempBoard->checkCell(i, j) == 'x') {
                    countPlayer++;
                } else if(tempBoard->checkCell(i, j) == 'o') {
                    countOther++;
                }
            } else if(playerType == whitePlayer) {
                if(tempBoard->checkCell(i, j) == 'o') {
                    countPlayer++;
                } else if(tempBoard->checkCell(i, j) == 'x') {
                    countOther++;
                }
            }
        }
    }
    delete tempBoard;
    //giving a grade to the move
    return countOther - countPlayer;
}