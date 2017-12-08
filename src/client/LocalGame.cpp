// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "LocalGame.h"

LocalGame::LocalGame(int boardSize, GameLogic* newGameLogic, Player* first, Player* second) {
    gameLogic = newGameLogic;
    board = new Board(boardSize);
    firstPlayer = first;
    secondPlayer = second;
}

LocalGame::~LocalGame() {
    delete board;
    delete firstPlayer;
    delete secondPlayer;
    delete gameLogic;
}

void LocalGame::assignTypes() {
    Player *tempPlayer;
    if(secondPlayer->getType() == notDefined) {
        firstPlayer->assignType(blackPlayer);
        secondPlayer->assignType(whitePlayer);
    } else if(secondPlayer->getType() == blackPlayer) {
        firstPlayer->assignType(whitePlayer);
        tempPlayer = firstPlayer;
        firstPlayer = secondPlayer;
        secondPlayer = tempPlayer;
    } else if(secondPlayer->getType() == whitePlayer) {
        firstPlayer->assignType(blackPlayer);
    }
}

void LocalGame::runGame() {
    vector<Point> options;
    Printer *printer = new ConsolePrinter();
    char winner;
    doOneTurn(options);
    winner = gameLogic->gameWon(*board);
    printer->printWinMessage(winner);
    delete printer;
}

void LocalGame::doOneTurn(vector<Point> options) {
    Player *current = firstPlayer, *waitingPlayer = secondPlayer, *tempPlayer;
    Printer *printer = new ConsolePrinter();
    type playerType;
    //runs the players turns untill there is a winner.
    while(true) {
        string xTest, yTest;
        int x = 0, y = 0;
        int *temp;
        playerType = current->getType();
        waitingPlayer->recieveOpponentsMove(x, y);
        options = gameLogic->availableMoves(*board, playerType);
        //if the current player has no available moves.
        if (options.size() == 0) {
            tempPlayer = current;
            current = waitingPlayer;
            waitingPlayer = tempPlayer;
            continue;
        }
        printer->printBoard(board);
        printer->printTurn(playerType);
        //print all move options.
        printer->printPossibleMoves(options);
        //let the player make a move.
        while (true) {
            //bool valid = true;
            printer->requestMove();
            Board *copyBoard = new Board(*board);
            temp = current->makeMove(*gameLogic, *copyBoard, options);
            delete copyBoard;
            x = temp[0];
            y = temp[1];
            //check if move is in board boundaries.
            if(!gameLogic->validOption(*board, x - 1, y - 1, options)) {
                break;
            } else {
                printer->printInvalidMove('o');
                continue;
            }
//            //checks if the move was declared valid.
//            if (valid) {
//                printer->printInvalidMove('i');
//            } else {
//                break;
//            }
        }
        printer->printMove(playerType, x, y);
        x -= 1, y -= 1;
        //flips the correct tiles according to the player and the players move.
        gameLogic->changeTiles(playerType, x, y, *board);
        if(gameLogic->gameFinalMove(*board, playerType, x, y)) {
            break;
        }
        tempPlayer = current;
        current = waitingPlayer;
        waitingPlayer = tempPlayer;
        delete temp;
    }
    printer->printBoard(board);
    delete printer;
}