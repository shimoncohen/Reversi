// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "StandartGameLogic.h"


void StandartGameLogic::changeTiles(type type, int x, int y, Board &board) {
    char o;
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
    board.putTile(x, y, type);
    //flip all of the valid move tiles.
    flipTiles(type, x + right, y + down, right, down, board);
}