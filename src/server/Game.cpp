// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Game.h"

Game::Game(string gameName, int socket1, int socket2) {
    name = gameName;
    firstPlayerSocket = socket1;
    secondPlayerSocket = socket2;
    status = 1;
}

string Game::getName() {
    return name;
}

bool Game::getStatus() {
    return status;
}

int Game::getFirstPlayer() {
    return firstPlayerSocket;
}

int Game::getSecondPlayer() {
    return secondPlayerSocket;
}