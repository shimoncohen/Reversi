// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Game.h"

Game::Game(int boardSize, GameLogic* newGameLogic, Player* first, Player* second) {
    gameLogic = newGameLogic;
    board = new Board(boardSize);
    firstPlayer = first;
    secondPlayer = second;
    turn = 0;
}

Game::~Game() {
    delete board;
    delete firstPlayer;
    delete secondPlayer;
    delete gameLogic;
}

void Game::runGame() {
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

void Game::doOneTurn(vector<Point> options) {
    bool noMoreTurns = false;
    Player *current;
    Printer *printer = new ConsolePrinter();
    char playerType = ' ';
    //runs the players turns untill there is a winner.
    while(true) {
        string xTest, yTest;
        int x = 0, y = 0;
        int *temp;
        if (turn == 0) {
            options = gameLogic->availableMoves(*board, blackPlayer);
            current = firstPlayer;
            playerType = 'x';
        } else {
            options = gameLogic->availableMoves(*board, whitePlayer);
            current = secondPlayer;
            playerType = 'o';
        }
        //if the current player has no available moves.
        if (options.size() == 0) {
            if(noMoreTurns) {
                break;
            }
            noMoreTurns = true;
            turn += 1;
            turn %= 2;
            continue;
        }
        board->print();
        if (turn == 0) {
            printer->printTurn('X');
        } else {
            printer->printTurn('O');
        }
        //print all move options.
        printer->printPossibleMoves(options);
        cout << endl << endl;
        //let the player make a move.
        while (true) {
            bool valid = true;
            printer->requestMove();
            Board *copyBoard = new Board(*board);
            temp = current->makeMove(*gameLogic, *copyBoard, options);
            delete copyBoard;
            x = temp[0];
            y = temp[1];
            if (x > 0 && y > 0 && x <= board->getSize() && y <= board->getSize()) {
                for (int i = 0; i < options.size(); i++) {
                    if (x == options[i].getX() && y == options[i].getY()) {
                        valid = false;
                        break;
                    }
                }
            } else {
                printer->printInvalidMove('o');
                x = 0;
                y = 0;
                continue;
            }
            //checks if the move was declared valid.
            if (valid) {
                printer->printInvalidMove('i');
                x = 0;
                y = 0;
            } else {
                break;
            }
        }
        printer->printMove(playerType, x, y);
        x -= 1;
        y -= 1;
        if (turn == 0) {
            board->putTile(x, y, 'x');
            //flips the correct tiles according to the player and the players move.
            gameLogic->changeTiles(blackPlayer, x, y, *board);
            turn = 1;
        } else {
            board->putTile(x, y, 'o');
            gameLogic->changeTiles(whitePlayer, x, y, *board);
            turn = 0;
        }
        noMoreTurns = false;
        delete temp;
    }
    delete printer;
    cout << *board;
}