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
    /*
     * end of game: TODO
     */
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
        if(playerType != player->getType()) {
            recivedInfo = ((ServerPlayer*)player)->getMove();
            //board->extractBoardFromString(recivedInfo.board);
            if(player->getType() == whitePlayer) {
                board->putTile(recivedInfo.x, recivedInfo.y, 'x');
                gameLogic->changeTiles(blackPlayer, recivedInfo.x, recivedInfo.y, *board);
            } else {
                board->putTile(recivedInfo.x, recivedInfo.y, 'o');
                gameLogic->changeTiles(whitePlayer, recivedInfo.x, recivedInfo.y, *board);
            }
        }
        options = gameLogic->availableMoves(*board, player->getType());
        //if the current player has no available moves.
        if (options.size() == 0) {
            if(noMoreTurns) {
                break;
            }
            noMoreTurns = true;
            turn += 1;
            turn %= 2;
            /* TODO
             * no moves
             */
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
        printer->printMove(playerType, x, y);
        x -= 1;
        y -= 1;
        if (playerType == player->getType()) {
            if(playerType == blackPlayer) {
                board->putTile(x, y, 'x');
            } else {
                board->putTile(x, y, 'o');
            }
            //flips the correct tiles according to the player and the players move.
            gameLogic->changeTiles(player->getType(), x, y, *board);
        }
        noMoreTurns = false;
        delete temp;
        cout << "Sending move: " << x << " " << y << endl;
        try {
            ((ServerPlayer *) player)->sendMove(*board, x, y);
        } catch (const char *msg) {
            cout << "Failed to send exercise to server.Reason: " << msg << endl;
        }
        if(playerType == blackPlayer) {
            playerType = whitePlayer;
        } else {
            playerType = blackPlayer;
        }
    }
    printer->printBoard(board);

}