/*shimon cohen*/
/*315383133*/

#include "StandartGameLogic.h"


void StandartGameLogic::changeTiles(type type, int x, int y, Board &board) {
    char o;
    if(type == black) {
        o = 'x';//players piece, to search for valid flips.
    } else {
        o = 'o';
    }
    for(int i = -1; i <= 1; i++) {//go over the board cells.
        for(int k = -1; k <= 1; k++) {
            if ((i != 0 || k != 0) && validMove(board, x, y, i, k, o, 0)) {//if the cell is a valid move.
                flipTiles(o, x + i, y + k, i, k, board);//flip all of the tiles for each valid move.
            }
        }
    }
}

vector<Point> StandartGameLogic::availableMoves(Board &board, type type1) {
    char a, o;
    vector<Point> options;
    if(type1 == black) {
        a = 'o';//other players piece, to search for valid move.
        o = 'x';
    } else {
        a = 'x';
        o = 'o';
    }
    for(int i = 0; i < board.getSize(); i++) {//go over the board cells.
        for(int k = 0; k < board.getSize(); k++) {
            if (board.checkCell(i, k) == ' ') {//if the cell is empty.
                bool exists = false;
                for(int j = -1; j <= 1; j++) {//check all adjacent cells.
                    for(int s = -1; s <= 1; s++) {
                        if (board.checkCell(i + j, k + s) == a && validMove(board, i + j, k + s, j, s, o, 0)) {//if the adjacent cell has the other players piece and its a valid move.
                            exists = true;
                        }
                    }
                }
                if(exists) {
                    options.push_back(Point(i + 1, k + 1));//add the cell as a valid move.
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
    validMove(board, x + right, y + down, right, down, piece, iteration + 1);//continue checking the board in the same direction.
}

void StandartGameLogic::flipTiles(char type, int x, int y, int right, int down, Board &board) {
    if(board.checkCell(x, y) == type || board.checkCell(x, y) == ' ' || (x > board.getSize() || y > board.getSize() || x < 0 || y < 0)) {
        return;
    }
    board.putTile(x, y, type);
    flipTiles(type, x + right, y + down, right, down, board);//flip all of the valid move tiles.
}