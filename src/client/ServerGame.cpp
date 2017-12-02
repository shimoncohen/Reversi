//
// Created by shimon on 12/3/17.
//

#include "ServerGame.h"

ServerGame::ServerGame(int boardSize, GameLogic* newGameLogic, Player* first, Player* second) {
    gameLogic = newGameLogic;
    board = new Board(boardSize);
    firstPlayer = first;
    secondPlayer = second;
    turn = 0;
}

ServerGame::~ServerGame() {
    delete board;
    delete firstPlayer;
    delete secondPlayer;
    delete gameLogic;
}

void ServerGame::runGame() {

}

void ServerGame::doOneTurn(vector<Point> v) {

}