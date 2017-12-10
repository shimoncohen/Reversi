// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "ConsolePrinter.h"

void ConsolePrinter::printGameOpenning() {
    cout << "Welcome to Reversi!" << endl << endl << "Choose an opponent type:" << endl;
    cout << "1. a human local player" << endl << "2. an AI player" << endl << "3. a remote player" << endl;
}

void ConsolePrinter::connectedToServerMessage() {
    cout << "Connected to server" << endl;
}

void ConsolePrinter::waitingForConnectionMessage() {
    cout << "Waiting for opponent to join..." << endl;
}

void ConsolePrinter::failedMessage(const char *msg) {
    cout << msg << endl;
}

void ConsolePrinter::printInvalidGameMode() {
    cout << "Invalid option." << endl << endl;
    cout << "which mode would you like to play?" << endl;
    cout << "1. a human local player" << endl << "2. an AI player" << endl << "3. a remote player" << endl;
}

void ConsolePrinter::boardSizeMessage() {
    cout << "Please insert a valid board size (must be greater than or equal to four):" << endl;
}

void ConsolePrinter::waitingMessage() {
    cout << "Waiting for opponents move..." << endl << endl;
}

void ConsolePrinter::printTurn(type playerType) {
    if(playerType == blackPlayer) {
        cout << "X: it's your move." << endl;
    } else {
        cout << "O: it's your move." << endl;
    }
}

void ConsolePrinter::requestMove() {
    cout << "Please enter your move row col: ";
}

void ConsolePrinter::printMove(type playerType, int x, int y) {
    if(playerType == blackPlayer) {
        cout << "X played " << x << " " << y << endl;
    } else {
        cout << "O played " << x << " " << y << endl;
    }
}

void ConsolePrinter::printPoint(int* point) {
    cout << point[0] << " " << point[1] << endl;
}

void ConsolePrinter::printBoard(Board *board) const {
    cout << *board;
}

void ConsolePrinter::printInvalidMove() {
    cout << "invalid move!" << endl << endl;
}

void ConsolePrinter::printPossibleMoves(vector<Point> possibleMoves) {
    cout << "Your possible moves: ";
    // go over the vector and print the points it contains.
    for (int k = 0; k < possibleMoves.size(); k++) {
        if(k != 0) {
            cout << ",";
        }
        cout << "(" << possibleMoves[k].getX() << "," << possibleMoves[k].getY() << ")";
    }
    cout << endl << endl;
}

void ConsolePrinter::printNoMoves(type playerType) {
    if(playerType == blackPlayer) {
        cout << endl << "X has no available moves!" << endl << "Turn goes to opponent." << endl;
    } else if(playerType == whitePlayer) {
        cout << endl << "O has no available moves!" << endl << "Turn goes to opponent." << endl;
    }
}

void ConsolePrinter::printOpponentHasNoMoves() {
    cout << "Opponent has no available moves!" << endl;
}

void ConsolePrinter::printWinMessage(char winner) {
    // if the char is t then the game ended in a tie.
    if(winner == 't') {
        cout << "it's a tie!" << endl;
        // else print the winner message.
    } else {
        cout << winner << " wins!" << endl;
    }
}