// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Game.h"

Game::Game(int boardSize, GameLogic* newGameLogic, Player* first, Player* second) {
    gameLogic = newGameLogic;
    board = new Board(boardSize);
    firstPlayer = first;
    secondPlayer = second;
}

Game::Game(GameLogic *newGameLogic, Player *first, Player *second) {
    gameLogic = newGameLogic;
    board = new Board();
    firstPlayer = first;
    secondPlayer = second;
}

Game::~Game() {
    delete board;
    delete firstPlayer;
    delete secondPlayer;
    delete gameLogic;
}

void Game::assignTypes() {
    Player *tempPlayer;
    // if the second player is not defined we will assign the first to black and the second to white
    if(secondPlayer->getType() == notDefined) {
        firstPlayer->assignType(blackPlayer);
        secondPlayer->assignType(whitePlayer);
    // if the second is assigned as black we will assign the second as black and the first as white
    } else if(secondPlayer->getType() == blackPlayer) {
        firstPlayer->assignType(whitePlayer);
        tempPlayer = firstPlayer;
        firstPlayer = secondPlayer;
        secondPlayer = tempPlayer;
    // if the second is assigned as white we will assign the first to black
    } else if(secondPlayer->getType() == whitePlayer) {
        firstPlayer->assignType(blackPlayer);
    }
}

void Game::runGame() {
    vector<Point> options;
    Printer *printer = new ConsolePrinter();
    // represents the winner player
    char winner;
    assignTypes();
    //starts the game
    try {
    doOneTurn(options);
    } catch (const char* msg) {
        delete printer;
        throw msg;
    }
    winner = gameLogic->gameWon(*board);
    //printing as wiining message
    printer->printWinMessage(winner);
    delete printer;
}

void Game::doOneTurn(vector<Point> options) {
    Player *current = firstPlayer, *waitingPlayer = secondPlayer, *tempPlayer;
    Printer *printer = new ConsolePrinter();
    type playerType;
    int x = -10, y = -10;
    int *temp;
    int valid;
    bool end = false;
    //runs the players turns until there is a winner.
    while (true) {
        string xTest, yTest;
        playerType = current->getType();
        // in case of server game writes the opponent's move into the socket
        try {
            current->recieveOpponentsMove(x, y);
        } catch (const char* msg) {
            delete printer;
            throw msg;
        }
        // in case the game ends
        if(end) {
            if(x == END && y == END) {
                waitingPlayer->recieveOpponentsMove(END, END);
            } else {
                waitingPlayer->recieveOpponentsMove(CLOSE, CLOSE);
            }
            break;
        }
        // returns the vector of the player's available moves
        options = gameLogic->availableMoves(*board, playerType);
        //if the current player has no available moves.
        if (options.size() == 0) {
            printer->printNoMoves(playerType);
            //in case of no mor moves printing a message and switch between the players.
            tempPlayer = current;
            current = waitingPlayer;
            waitingPlayer = tempPlayer;
            continue;
        }
        // printing the board and which player is going to play.
        printer->printBoard(board);
        printer->printTurn(playerType);
        if(current->needPrint()) {
            //print all move options.
            printer->printPossibleMoves(options);
            // print a request for a move fro the player.
            printer->requestMove();
        }
        //let the player make a move.
        while (true) {
            Board *copyBoard = new Board(*board);
            try {
                temp = current->makeMove(*gameLogic, *copyBoard, options);
            } catch (const char* msg) {
                delete copyBoard;
                delete printer;
                throw msg;
            }
            if(temp[0] == END && temp[1] == END) {
                end = true;
                x = -2;
                y = -2;
                break;
            } else if(temp[0] == CLOSE && temp[1] == CLOSE) {
                end = true;
                x = -3;
                y = -3;
                break;
            }
            delete copyBoard;
            x = temp[0] + 1;
            y = temp[1] + 1;
            delete[] temp;
            //check if move is in board boundaries.
            valid = gameLogic->validOption(*board, x, y , options);
            if (valid) {
                break;
            } else {
                printer->printInvalidMove();
                continue;
            }
        }
        if(end) {
            continue;
        }
        x -= 1, y -= 1;
        printer->printMove(playerType, x + 1, y + 1);
        //flips the correct tiles according to the player and the players move.
        gameLogic->changeTiles(playerType, x, y, *board);
        // check if the current move ends the game
        if (gameLogic->gameFinalMove(*board, playerType, x, y)) {
            waitingPlayer->recieveOpponentsMove(x, y);
            end = true;
        }
        // switching between the players
        tempPlayer = current;
        current = waitingPlayer;
        waitingPlayer = tempPlayer;
    }
    printer->printBoard(board);
    delete printer;
}