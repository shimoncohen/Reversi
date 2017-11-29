// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "ConsolePrinter.h"

void ConsolePrinter::printGameOpenning() {
    cout << "Reversi!" << endl << "Welcome to the game menu" << endl << "which mode would you like to play?" << endl;
    cout << "1) Player VS Player" << endl << "2) Player VS Computer(AI)" << endl;
}

void ConsolePrinter::printInvalidGameMode() {
    cout << "Invalid option." << endl << endl;
    cout << "which mode would you like to play?" << endl;
    cout << "1) Player VS Player" << endl << "2) Player VS Computer(AI)" << endl;
}

void ConsolePrinter::boardSizeMessage() {
    cout << "Please insert a valid board size (must be greater than or equal to four):" << endl;
}

void ConsolePrinter::startGameMessage() {
    cout << "Start game!" << endl << endl;
}

void ConsolePrinter::printTurn(char type) {
    cout << type << " it's your move." << endl;
}

void ConsolePrinter::requestMove() {
    cout << "Please enter your move row col: ";
}

void ConsolePrinter::printMove(char playerType, int x, int y) {
    cout << endl << playerType << " played " << x << " " << y << endl;
}

void ConsolePrinter::printPoint(int* point) {
    cout << point[0] << " " << point[1] << endl;
}

void ConsolePrinter::printBoard(Board *board) const {
    cout << *board;
}

void ConsolePrinter::printInvalidMove(char outIn) {
    // if char is i then the invalid move is in the board.
    if(outIn == 'i') {
        cout << "invalid move!" << endl << endl;
        // else the invalid move was out of the board boundaries
    } else if(outIn == 'o') {
        cout << "ERROR: move out of board boundries" << endl << endl;
    }
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

void ConsolePrinter::printWinMessage(char winner) {
    // if the char is t then the game ended in a tie.
    if(winner == 't') {
        cout << "it's a tie!" << endl;
        // else print the winner message.
    } else {
        cout << winner << " wins!" << endl;
    }
}