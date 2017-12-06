// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "LocalGame.h"

LocalGame::LocalGame(int boardSize, GameLogic* newGameLogic, Player* first, Player* second) {
    gameLogic = newGameLogic;
    board = new Board(boardSize);
    firstPlayer = first;
    secondPlayer = second;
    turn = 0;
}

LocalGame::~LocalGame() {
    delete board;
    delete firstPlayer;
    delete secondPlayer;
    delete gameLogic;
}

void LocalGame::runGame() {
    vector<Point> options;
    Printer *printer = new ConsolePrinter();
    doOneTurn(options);
    int blackPieces = 0, whitePieces = 0;
    //counts the black and white pieces on the board.
    for(int i = 0; i < board->getSize(); i++) {
        for(int k = 0; k < board->getSize(); k++) {
            if(board->checkCell(i, k) == 'x') {
                blackPieces++;
            } else {
                whitePieces++;
            }
        }
    }
    //declares the winner depending by the amount of pieces each player has on the board.
    if(blackPieces > whitePieces) {
        printer->printWinMessage('X');
    } else if(whitePieces > blackPieces) {
        printer->printWinMessage('O');
    } else {
        printer->printWinMessage('t');
    }
    delete printer;
}

void LocalGame::doOneTurn(vector<Point> options) {
    bool noMoreTurns = false;
    Player *current = firstPlayer, *waitingPlayer = secondPlayer, *tempPlayer;
    Printer *printer = new ConsolePrinter();
    type playerType;
    //runs the players turns untill there is a winner.
    while(true) {
        string xTest, yTest;
        int x = 0, y = 0;
        int *temp;
        playerType = current->getType();
        options = gameLogic->availableMoves(*board, playerType);
        //if the current player has no available moves.
        if (options.size() == 0) {
            if(noMoreTurns) {
                break;
            }
            noMoreTurns = true;
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
            bool valid = true;
            printer->requestMove();
            Board *copyBoard = new Board(*board);
            temp = current->makeMove(*gameLogic, *copyBoard, options);
            delete copyBoard;
            x = temp[0];
            y = temp[1];
            //check if move is in board boundaries.
            if (x > 0 && y > 0 && x <= board->getSize() && y <= board->getSize()) {
                //go over all of the possible moves.
                for (int i = 0; i < options.size(); i++) {
                    //if the move is a possible move.
                    if (x == options[i].getX() && y == options[i].getY()) {
                        valid = false;
                        break;
                    }
                }
            } else {
                printer->printInvalidMove('o');
                continue;
            }
            //checks if the move was declared valid.
            if (valid) {
                printer->printInvalidMove('i');
            } else {
                break;
            }
        }
        printer->printMove(playerType, x, y);
        x -= 1, y -= 1;
        board->putTile(x, y, playerType);
        //flips the correct tiles according to the player and the players move.
        gameLogic->changeTiles(playerType, x, y, *board);
        tempPlayer = current;
        current = waitingPlayer;
        waitingPlayer = tempPlayer;
        noMoreTurns = false;
        delete temp;
    }
    printer->printBoard(board);
    delete printer;
}