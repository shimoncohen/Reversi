// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StandartGameLogic.h"

vector<Point> StandartGameLogic::availableMoves(Board &board, type type1) {
    char a, o;
    vector<Point> options;
    if(type1 == blackPlayer) {
        //other players piece, to search for valid move.
        a = 'o';
        o = 'x';
    } else {
        a = 'x';
        o = 'o';
    }
    //go over the board cells.
    for(int i = 0; i < board.getSize(); i++) {
        for(int k = 0; k < board.getSize(); k++) {
            //if the cell is empty.
            if (board.checkCell(i, k) == ' ') {
                bool exists = false;
                //check all adjacent cells.
                for(int j = -1; j <= 1; j++) {
                    for(int s = -1; s <= 1; s++) {
                        //if the adjacent cell has the other players piece and its a valid move.
                        if (board.checkCell(i + j, k + s) == a && validMove(board, i + j, k + s, j, s, o, 0)) {
                            exists = true;
                        }
                    }
                }
                if(exists) {
                    //add the cell as a valid move.
                    options.push_back(Point(i + 1, k + 1));
                }
            }
        }
    }
    return options;
}

bool StandartGameLogic::validOption(Board &board, int x, int y, vector<Point> options) {
    if(isGameWon(board)) {
        return true;
    }
    if (x > 0 && y > 0 && x <= board.getSize() && y <= board.getSize()) {
        //go over all of the possible moves.
        for (int i = 0; i < options.size(); i++) {
            //if the move is a possible move.
            if (x == options[i].getX() && y == options[i].getY()) {
                return true;
            }
        }
    }
    return false;
}

void StandartGameLogic::changeTiles(type type, int x, int y, Board &board) {
    char o;
    board.putTile(x, y, type);
    if(type == blackPlayer) {
        //players piece, to search for valid flips.
        o = 'x';
    } else {
        o = 'o';
    }
    //go over the board cells.
    for(int i = -1; i <= 1; i++) {
        for(int k = -1; k <= 1; k++) {
            //if the cell is a valid move.
            if ((i != 0 || k != 0) && validMove(board, x, y, i, k, o, 0)) {
                //flip all of the tiles for each valid move.
                flipTiles(o, x + i, y + k, i, k, board);
            }
        }
    }
}

char StandartGameLogic::gameWon(Board &board) {
    int blackPieces = 0, whitePieces = 0;
    //counts the black and white pieces on the board.
    for(int i = 0; i < board.getSize(); i++) {
        for(int k = 0; k < board.getSize(); k++) {
            if(board.checkCell(i, k) == 'x') {
                blackPieces++;
            } else if(board.checkCell(i, k) == 'o'){
                whitePieces++;
            }
        }
    }
    //declares the winner depending by the amount of pieces each player has on the board.
    if(blackPieces > whitePieces) {
        return 'X';
    } else if(whitePieces > blackPieces) {
        return 'O';
    } else {
        return 't';
    }
}

bool StandartGameLogic::isGameWon(Board &board) {
    //check if board is full.
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.checkCell(i, j) == ' ') {
                return false;
            }
        }
    }
    return false;
}

bool StandartGameLogic::gameFinalMove(Board &board, type pType, int x, int y) {
    if (x == -2 && y == -2) {
        return true;
    }
    vector<Point> moves = availableMoves(board, pType);
    if(moves.empty()) {
        if(pType == blackPlayer) {
            moves = availableMoves(board, whitePlayer);
        } else {
            moves = availableMoves(board, blackPlayer);
        }
        if(moves.empty()) {
            return true;
        }
    }
    return false;
}

bool StandartGameLogic::validMove(Board &board, int x, int y, int right, int down, char piece, int iteration) {
    if(x > board.getSize() || y > board.getSize() || x < 0 || y < 0 || board.checkCell(x, y) == ' ') {
        return false;
    }
    if(iteration > 0 && board.checkCell(x, y) == piece) {
        return true;
    }
    //continue checking the board in the same direction.
    validMove(board, x + right, y + down, right, down, piece, iteration + 1);
}

void StandartGameLogic::flipTiles(char type, int x, int y, int right, int down, Board &board) {
    if(board.checkCell(x, y) == type || board.checkCell(x, y) == ' '
       || (x > board.getSize() || y > board.getSize() || x < 0 || y < 0)) {
        return;
    }
    if(type == 'x') {
        board.putTile(x, y, blackPlayer);
    } else if(type == 'o') {
        board.putTile(x, y, whitePlayer);
    }
    //flip all of the valid move tiles.
    flipTiles(type, x + right, y + down, right, down, board);
}