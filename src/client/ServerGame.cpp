// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "ServerGame.h"

ServerGame::ServerGame(int boardSize, GameLogic* newGameLogic, Player* current) {
    gameLogic = newGameLogic;
    board = new Board(boardSize);
    player = current;
    turn = 0;
}

ServerGame::~ServerGame() {
    delete board;
    delete player;
    delete gameLogic;
}

void ServerGame::runGame() {
    vector<Point> options;
    Printer *printer = new ConsolePrinter();
    try {
        ((ServerPlayer*)player)->connectToServer();
    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
        return;
    }
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

void ServerGame::doOneTurn(vector<Point> options) {
    bool noMoreTurns = false;
    Printer *printer = new ConsolePrinter();
    type playerType = blackPlayer;
    Info recivedInfo;
    //runs the players turns untill there is a winner.
    while(true) {
        string xTest, yTest;
        int x = 0, y = 0;
        recivedInfo.x = 0;
        recivedInfo.y = 0;
        int *temp;
        // if it's the other player's turn, we will make his move on the current player board.
        if (playerType != player->getType()) {
            // reciving the other player move
            printer->waitingMessage();
            recivedInfo = ((ServerPlayer *) player)->getMove();
            //assigning values on the board according to the player's type.
            //if we are white, other is black, and the opposite.
            if(recivedInfo.x == -2 && recivedInfo.y == -2) {
                printer->printBoard(board);
                break;
            } if(recivedInfo.x != -1 && recivedInfo.y != -1) {
                if (player->getType() == whitePlayer) {
                    board->putTile(recivedInfo.x, recivedInfo.y, 'x');
                    gameLogic->changeTiles(blackPlayer, recivedInfo.x, recivedInfo.y, *board);
                    printer->printMove('X', recivedInfo.x + 1, recivedInfo.y + 1);
                } else {
                    board->putTile(recivedInfo.x, recivedInfo.y, 'o');
                    gameLogic->changeTiles(whitePlayer, recivedInfo.x, recivedInfo.y, *board);
                    printer->printMove('O', recivedInfo.x + 1, recivedInfo.y + 1);
                }
            } else {
                printer->printOpponentHasNoMoves();
            }
        } else {
            options = gameLogic->availableMoves(*board, player->getType());
            //if the current player has no available moves.
            if (options.size() == 0) {
                if (noMoreTurns) {
                    try {
                        ((ServerPlayer *) player)->sendMove(*board, -2, -2);
                    } catch (const char *msg) {
                        cout << "Failed to send exercise to server.Reason: " << msg << endl;
                    }
                    printer->printBoard(board);
                    break;
                }
                noMoreTurns = true;
                /* TODO
                 * no moves
                 */
                printer->printBoard(board);
                printer->printNoMoves();
                try {
                    ((ServerPlayer *) player)->sendMove(*board, -1, -1);
                } catch (const char *msg) {
                    cout << "Failed to send move to server.Reason: " << msg << endl;
                }
                if (playerType == blackPlayer) {
                    playerType = whitePlayer;
                } else {
                    playerType = blackPlayer;
                }
                continue;
            }
            printer->printBoard(board);
            printer->printTurn(player->getType());
            //print all move options.
            printer->printPossibleMoves(options);
            //let the player make a move.
            while (true) {
                bool valid = true;
                printer->requestMove();
                Board *copyBoard = new Board(*board);
                temp = player->makeMove(*gameLogic, *copyBoard, options);
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
            if (player->getType() == blackPlayer) {
                printer->printMove('X', x, y);
            } else {
                printer->printMove('O', x, y);
            }
            x -= 1;
            y -= 1;
            if (playerType == player->getType()) {
                if (playerType == blackPlayer) {
                    board->putTile(x, y, 'x');
                } else {
                    board->putTile(x, y, 'o');
                }
                //flips the correct tiles according to the player and the players move.
                gameLogic->changeTiles(player->getType(), x, y, *board);
            } else {
                if (playerType == whitePlayer) {
                    board->putTile(x, y, 'x');
                } else {
                    board->putTile(x, y, 'o');
                }
                //flips the correct tiles according to the player and the players move.
                gameLogic->changeTiles(player->getType(), x, y, *board);
            }
            noMoreTurns = false;
            delete temp;
            try {
                ((ServerPlayer *) player)->sendMove(*board, x, y);
            } catch (const char *msg) {
                cout << "Failed to send move to server.Reason: " << msg << endl;
            }
            printer->printBoard(board);
        }
        if (playerType == blackPlayer) {
            playerType = whitePlayer;
        } else {
            playerType = blackPlayer;
        }
    }
}