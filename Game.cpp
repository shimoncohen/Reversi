/*shimon cohen*/
/*315383133*/

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
    doOneTurn(options);
    int blackPieces = 0, whitePieces = 0;
    for(int i = 0; i < board->getSize(); i++) {//counts the black and white pieces on the board.
        for(int k = 0; k < board->getSize(); k++) {
            if(board->checkCell(i, k) == 'x') {
                blackPieces++;
            } else {
                whitePieces++;
            }
        }
    }
    if(blackPieces > whitePieces) {//declares the winner depending by the amount of pieces each player has on the board.
        cout << "X wins!" << endl;
    } else if(whitePieces > blackPieces) {
        cout << "O wins!" << endl;
    } else {
        cout << "it's a tie!" << endl;
    }
}

void Game::doOneTurn(vector<Point> options) {
    bool noMoreTurns = false;
    Player *current;
    while(true) {//runs the players turns untill there is a winner.
        string xTest, yTest;
        int x = 0, y = 0;
        type currentPlayer;
        //board->print();
//        if (board->getFreeCells() == 0) {//if the board has no free cells.
//            break;//end the game
//        }
        if (turn == 0) {
            options = gameLogic->availableMoves(*board, black);
            current = firstPlayer;
        } else {
            options = gameLogic->availableMoves(*board, white);
            current = secondPlayer;
        }
        if (options.size() == 0) {//if the current player has no available moves.
            if(noMoreTurns) {
                break;
            }
            noMoreTurns = true;
            turn += 1;
            turn %= 2;
            continue;
        }
        cout << *board;
        if (turn == 0) {
            cout << "X: it's your move." << endl;
        } else {
            cout << "O: it's your move." << endl;
        }
        cout << "Your possible moves: ";
        for (int k = 0; k < options.size(); k++) {//print all move options.
            if(k != 0) {
                cout << ",";
            }
            cout << "(" << options[k].getX() << "," << options[k].getY() << ")";
        }
        cout << endl << endl;
        while (true) {//let the player make a move.
            bool valid = true;
            cout << "Please enter your move row col: ";
            string *temp = current->makeMove(*gameLogic, board, options);
            xTest = temp[0];
            yTest = temp[1];
            for(int i = 0; i < xTest.size(); i++) {//check if what the user entered are numbers.
                if(!isdigit(xTest[i])) {
                    valid = false;
                }
            }
            for(int i = 0; i < yTest.size(); i++) {
                if(!isdigit(yTest[i])) {
                    valid = false;
                }
            }
            if(!valid) {
                cout << "Please enter numbers only." << endl << endl;
                continue;
            }
            for(int i = 0; i < xTest.size(); i++) {//if the user entered numbers the convert them to int.
                x *= 10;
                x += xTest[i] -48;
            }
            for(int i = 0; i < yTest.size(); i++) {
                y *= 10;
                y += yTest[i] -48;
            }
            if (x > 0 && y > 0 && x <= board->getSize() && y <= board->getSize()) {
                for (int i = 0; i < options.size(); i++) {
                    if (x == options[i].getX() && y == options[i].getY()) {
                        valid = false;
                        break;
                    }
                }
            } else {
                cout << "ERROR: move out of board boundries" << endl << endl;
                x = 0;
                y = 0;
                continue;
            }
            if (valid) {//checks if the move was declared valid.
                cout << "invalid move!" << endl << endl;
                x = 0;
                y = 0;
            } else {
                break;
            }
        }
        x -= 1;
        y -= 1;
        if (turn == 0) {
            board->putTile(x, y, 'x');
            gameLogic->changeTiles(black, x, y, *board);//flips the correct tiles according to the player and the players move.
            turn = 1;
        } else {
            board->putTile(x, y, 'o');
            gameLogic->changeTiles(white, x, y, *board);
            turn = 0;
        }
    }
    cout << *board;
}