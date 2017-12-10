// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "LocalGame.h"

#define END -2

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
    assignTypes();
    doOneTurn(options);
    winner = gameLogic->gameWon(*board);
    printer->printWinMessage(winner);
    delete printer;
}

void LocalGame::doOneTurn(vector<Point> options) {
    Player *current = firstPlayer, *waitingPlayer = secondPlayer, *tempPlayer;
    Printer *printer = new ConsolePrinter();
    type playerType;
    int x = -10, y = -10;
    int *temp;
    int valid;
    bool end = false;
    //runs the players turns untill there is a winner.
    while (true) {
        string xTest, yTest;
        playerType = current->getType();
        current->recieveOpponentsMove(x, y);
        if(end) {
            waitingPlayer->recieveOpponentsMove(END, END);
            break;
        }
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
        printer->requestMove();
        //let the player make a move.
        while (true) {
            //bool valid = true;
            Board *copyBoard = new Board(*board);
            temp = current->makeMove(*gameLogic, *copyBoard, options);
//                waitingPlayer->recieveOpponentsMove(temp[0], temp[1]);
            delete copyBoard;
            x = temp[0] + 1;
            y = temp[1] + 1;
            //check if move is in board boundaries.
            valid = gameLogic->validOption(*board, x, y , options);
            if (valid) {
                break;
            } else {
                printer->printInvalidMove('o');
                continue;
            }
        }
        x -= 1, y -= 1;
        printer->printMove(playerType, x + 1, y + 1);
        //flips the correct tiles according to the player and the players move.
        gameLogic->changeTiles(playerType, x, y, *board);
        if (gameLogic->gameFinalMove(*board, playerType, x, y)) {
            waitingPlayer->recieveOpponentsMove(x, y);
            end = true;
        }
        tempPlayer = current;
        current = waitingPlayer;
        waitingPlayer = tempPlayer;
    }
//    }
    printer->printBoard(board);
    delete temp;
    delete printer;
}