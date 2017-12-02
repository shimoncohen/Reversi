// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "AIPlayer.h"

AIPlayer::AIPlayer(type type1) {
    playerType = type1;
}

AIPlayer::~AIPlayer() {

}

int* AIPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    // copy board to simulate AI player's moves
    Board *simulator = new Board(board);
    ConsolePrinter printer;
    //set grade to maximum value
    int i = 0, minGrade = simulator->getSize() * simulator->getSize(), currentMinGrade;
    int *myMove = new int[2];
    // simulate each of AI player's moves
    for(i; i < moves.size(); i++) {
        currentMinGrade = checkMove(gameLogic, *simulator, moves[i]);
        // save the avaliable option with the lowest grade
        if(currentMinGrade < minGrade) {
            minGrade = currentMinGrade;
            myMove[0] = moves[i].getX();
            myMove[1] = moves[i].getY();
        }
    }
    delete simulator;
    printer.printPoint(myMove);
    return myMove;
}

int AIPlayer::checkMove(GameLogic &gameLogic, Board &board, Point point) {
    // copy board to simulate opponent's moves
    Board *opponentSimulator = new Board(board);
    int maxGrade = 0, currentMaxGrade;
    // vector of opponents moves
    vector<Point> opponentsMoves;
    if(playerType == blackPlayer) {
        opponentSimulator->putTile(point.getX() - 1, point.getY() - 1, 'x');
    } else {
        opponentSimulator->putTile(point.getX() - 1, point.getY() - 1, 'o');
    }
    gameLogic.changeTiles(playerType, point.getX() - 1, point.getY() - 1, *opponentSimulator);
    // check opponents possible moves according to his type
    if(playerType == blackPlayer) {
        opponentsMoves = gameLogic.availableMoves(*opponentSimulator, whitePlayer);
    } else {
        opponentsMoves = gameLogic.availableMoves(*opponentSimulator, blackPlayer);
    }
    // if the opponent has no moves.
    if(opponentsMoves.size() == 0) {
        delete opponentSimulator;
        return -1;
    }
    // if the opponent had possible moves then check all the moves and grade each one
    for(int i = 0; i < opponentsMoves.size(); i++) {
        currentMaxGrade = gradeMove(gameLogic, *opponentSimulator, opponentsMoves[i]);
        // save the lowest grade
        if(currentMaxGrade > maxGrade) {
            maxGrade = currentMaxGrade;
        }
    }
    delete opponentSimulator;
    return maxGrade;
}

int AIPlayer::gradeMove(GameLogic &gameLogic, Board &board, Point move) {
    //coping the board
    Board *tempBoard = new Board(board);
    int countPlayer = 0, countOther = 0;
    type otherPlayerType;
    ///making the move on the new board
    if(playerType == blackPlayer) {
        otherPlayerType = whitePlayer;
        tempBoard->putTile(move.getX() - 1, move.getY() - 1, 'o');
    } else {
        otherPlayerType = blackPlayer;
        tempBoard->putTile(move.getX() - 1, move.getY() - 1, 'x');
    }
    gameLogic.changeTiles(otherPlayerType, move.getX() - 1, move.getY() - 1, *tempBoard);
    //counting the x's and the o's on the board
    for(int i = 0; i < tempBoard->getSize(); i++) {
        for(int j = 0; j < tempBoard->getSize(); j++) {
            //update counters according to player type.
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