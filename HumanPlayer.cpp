//
// Created by shimon on 11/5/17.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(type type1) {
    playerType = type1;
}

string* HumanPlayer::makeMove(GameLogic &gameLogic, Board *board, vector<Point> &moves) {
    string x, y;
    cin >> x >> y;
    string* a = new string[2];
    a[0] = x;
    a[1] = y;
    return a;
}