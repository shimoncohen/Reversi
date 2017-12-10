// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include <cstdio>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {
    playerType = notDefined;
}

HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::assignType(type playerType1) {
    playerType = playerType1;
}

type HumanPlayer::getType() {
    return playerType;
}

int* HumanPlayer::makeMove(GameLogic &gameLogic, Board &board, vector<Point> &moves) {
    string temp1, temp2;
    int *choice = new int[2];
    choice[0] = 0;
    choice[1] = 0;
    cin >> temp1 >> temp2;
    //check if what the user entered are numbers.
    for (int i = 0; i < temp1.size(); i++) {
        if (!isdigit(temp1[i])) {
            choice[0] = 0;
            choice[1] = 0;
            return choice;
        }
    }
    for (int i = 0; i < temp2.size(); i++) {
        if (!isdigit(temp2[i])) {
            choice[0] = 0;
            choice[1] = 0;
            return choice;
        }
    }
    //if the user entered numbers the convert them to int.
    for(int i = 0; i < temp1.size(); i++) {
        choice[0] *= 10;
        choice[0] += temp1[i] - 48;
    }
    for(int i = 0; i < temp2.size(); i++) {
        choice[1] *= 10;
        choice[1] += temp2[i] - 48;
    }
    choice[0] -= 1;
    choice[1] -= 1;
    return choice;
}

void HumanPlayer::recieveOpponentsMove(int x, int y) {
    return;
}