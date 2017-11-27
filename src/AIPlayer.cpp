/*shimon cohen*/
/*315383133*/

#include "AIPlayer.h"
#include <stdlib.h>

AIPlayer::AIPlayer(type type1) {
    playerType = type1;
}

AIPlayer::~AIPlayer() {

}

int* AIPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    Board *simulator = new ConsoleBoard(board);
    //string *finalDecision = new string[2];
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
//    if(myMove[0] == 0 || myMove[1] == 0) {
//        myMove[0] == -1;
//        myMove[1] == -1;
//    }
    // print AI's move.
    cout << myMove[0] << " " << myMove[1] << endl;
    return myMove;
}

int AIPlayer::checkMove(GameLogic &gameLogic, Board &board, Point point) {
    Board *opponentSimulator = new ConsoleBoard(board);
    int i = 0, minGrade = opponentSimulator->getSize() * opponentSimulator->getSize(), currentMinGrade;
    vector<Point> opponentsMoves;
    gameLogic.changeTiles(playerType, point.getX(), point.getY(), *opponentSimulator);
    if(playerType == blackPlayer) {
        opponentsMoves = gameLogic.availableMoves(*opponentSimulator, whitePlayer);
    } else {
        opponentsMoves = gameLogic.availableMoves(*opponentSimulator, blackPlayer);
    }
    if(opponentsMoves.size() == 0) {
        return -1;
    }
    for(i; i < opponentsMoves.size(); i++) {
        currentMinGrade = gradeMove(gameLogic, board, opponentsMoves[i]);
        if(minGrade > currentMinGrade) {
            minGrade = currentMinGrade;
        }
    }
    return minGrade;
}

//int AIPlayer::checkOpponentsMove(GameLogic &gameLogic, Board &board, Point move) {
//    Board *b = new ConsoleBoard(board);
//    vector<Point> playerMoves;
//    int i = 0, minGrade = b->getSize() * b->getSize(), currentMinGrade;
//    if(playerType == black) {
//        gameLogic.changeTiles(whitePlayer, move.getX(), move.getY(), *b);
//        playerMoves = gameLogic.availableMoves(*b, blackPlayer);
//    } else if(playerType == white) {
//        gameLogic.changeTiles(blackPlayer, move.getX(), move.getY(), *b);
//        playerMoves = gameLogic.availableMoves(*b, whitePlayer);
//    }
//    for(i; i < playerMoves.size(); i++) {
//        currentMinGrade = gradeMove(gameLogic, *b, playerMoves[i]);
//        if(currentMinGrade < minGrade) {
//            minGrade = currentMinGrade;
//        }
//    }
//    return minGrade;
//}

int AIPlayer::gradeMove(GameLogic &gamLogic, Board &board, Point move) {
    //coping the board
    Board *b = new ConsoleBoard(board);
    int countPlayer = 0, countOther = 0;
    ///making the move on the new board
    gamLogic.changeTiles(playerType, move.getX(), move.getY(), *b);
    //counting the x's and the o's on the board
    for(int i = 0; i < b->getSize(); i++) {
        for(int j = 0; j < b->getSize(); j++) {
            if(playerType == blackPlayer) {
                if(b->checkCell(i, j) == 'x') {
                    countPlayer++;
                } else if(b->checkCell(i, j) == 'o') {
                    countOther++;
                }
            } else if(playerType == whitePlayer) {
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