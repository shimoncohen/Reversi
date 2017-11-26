/*shimon cohen*/
/*315383133*/

#include "Board.h"

Board::Board(int size) {
    boardSize = size;
    board = new char*[size];
    for(int i = 0; i < size; i++) {
        board[i] = new char[size];
    }
    for(int i = 0; i < size; i++) {//fill the board cells with spaces to indicate free spaces.
        for(int k = 0; k < size; k++) {
            board[i][k] = ' ';
        }
    }
    board[size / 2 - 1][size / 2 - 1] = 'o';
    board[size / 2 - 1][size / 2] = 'x';
    board[size / 2][size / 2 - 1] = 'x';
    board[size / 2][size / 2] = 'o';
}

Board::Board(Board *board1) {
    boardSize = board1->getSize();
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            board[i][j] = board1->checkCell(i, j);
        }
    }
}

Board::~Board() {
    for(int i = 0; i < boardSize; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void Board::print() {
    if(boardSize > 9) {
        cout << "  ";
    } else {
        cout << " ";
    }
    for(int i = 1; i <= boardSize; i++) {
        cout << "| " << i << " ";
    }
    cout << "|" << endl;
    cout << "--";
    for(int k = 0; k < boardSize; k++) {
        if(k > 8) {
            cout << "-----";
            continue;
        }
        cout << "----";
    }
    cout << endl;
    for(int i = 0; i < boardSize; i++) {
        cout << i + 1;
        if(boardSize > 9 && i < 9) {
            cout << " ";
        }
        cout << "| ";
        for(int k = 0; k < boardSize; k++) {
            cout << board[i][k];
            if(k > 7) {
                cout << " |  ";
            } else {
                cout << " | ";
            }
            if(k == boardSize - 1) {
                cout << endl;
            }
        }
        cout << "--";
        for(int k = 0; k < boardSize; k++) {
            if(k > 8) {
                cout << "-----";
                continue;
            }
            cout << "----";
        }
        cout << endl;
    }
}

int Board::getSize() {
    return boardSize;
}

char Board::checkCell(const int x, const int y) {
    if(x < 0 || x >= boardSize || y < 0 || y >= boardSize) {//if the cell is out of the boards bounds.
        return ' ';
    }
    return board[x][y];
}

void Board::putTile(const int x, const int y, const char type) {
    board[x][y] = type;
}

ostream &operator <<(ostream &out, Board &board1) {
    if(board1.getSize() > 9) {
        out << "  ";
    } else {
        out << " ";
    }
    for(int i = 1; i <= board1.getSize(); i++) {
        out << "| " << i << " ";
    }
    out << "|" << endl;
    out << "--";
    for(int k = 0; k < board1.getSize(); k++) {
        if(k > 8) {
            out << "-----";
            continue;
        }
        out << "----";
    }
    out << endl;
    for(int i = 0; i < board1.getSize(); i++) {
        out << i + 1;
        if(board1.getSize() > 9 && i < 9) {
            cout << " ";
        }
        out << "| ";
        for(int k = 0; k < board1.getSize(); k++) {
            out << board1.checkCell(i, k);
            if(k > 7) {
                out << " |  ";
            } else {
                out << " | ";
            }
            if(k == board1.getSize() - 1) {
                out << endl;
            }
        }
        out << "--";
        for(int k = 0; k < board1.getSize(); k++) {
            if(k > 8) {
                out << "-----";
                continue;
            }
            out << "----";
        }
        out << endl;
    }
    return out;
}