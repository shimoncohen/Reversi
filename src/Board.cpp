/*shimon cohen*/
/*315383133*/

#include "Board.h"

Board::Board(int size) {
    boardSize = size;
    board = new boardChar*[size];
    for(int i = 0; i < size; i++) {
        board[i] = new boardChar[size];
    }
    for(int i = 0; i < size; i++) {//fill the board cells with spaces to indicate free spaces.
        for(int k = 0; k < size; k++) {
            board[i][k] = space;
        }
    }
    board[size / 2 - 1][size / 2 - 1] = white;
    board[size / 2 - 1][size / 2] = black;
    board[size / 2][size / 2 - 1] = black;
    board[size / 2][size / 2] = white;
}

Board::Board(Board &board1) {
    boardSize = board1.getSize();
    board = new boardChar *[boardSize];
    for (int i = 0; i < boardSize; i++) {
        board[i] = new boardChar[boardSize];
    }
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board1.checkCell(i, j) == black) {
                board[i][j] = black;
            } else if (board1.checkCell(i, j) == white) {
                board[i][j] = white;
            } else {
                board[i][j] = space;
            }
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
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {//if the cell is out of the boards bounds.
        return space;
    }
    if (board[x][y] == black) {
        return 'x';
    } else if (board[x][y] == white) {
        return 'o';
    }
    return ' ';
}

void Board::putTile(const int x, const int y, const char type) {
    if(type == 'x') {
        board[x][y] = black;
    } else if(type == 'o') {
        board[x][y] = white;
    } else {
        board[x][y] == space;
    }
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

bool operator ==(Board &board1, Board &board2) {
    int i = 0, k = 0;
    for(i; i < board1.getSize(); i++) {
        for(k; k < board1.getSize(); k++) {
            if(board1.checkCell(i,k) != board2.checkCell(i, k)) {
                return false;
            }
        }
    }
    return true;
}