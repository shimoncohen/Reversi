// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "LocalGame.h"

int main() {
	int size, choice = 0;
    Printer *printer = new ConsolePrinter();
    printer->printGameOpenning();
    // choosing game style. 1) PvP . 2) PvAI.
    cin >> choice;
    // dealing with impossible option
    while(choice != 1 && choice != 2) {
        printer->printInvalidGameMode();
        cin >> choice;
    }
    // getting board size from the user
    printer->boardSizeMessage();
    cin >> size;
    //dealing with size < 4
	while(size < 4) {
        printer->boardSizeMessage();
        cin >> size;
    }
    // creating game logic
    GameLogic* gameLogic = new StandartGameLogic();
    Player *first = new HumanPlayer(blackPlayer);
    Player *second;
    // creating the second player according to the game style (Player/ AI).
    switch(choice) {
        case 1:
            second = new HumanPlayer(whitePlayer);
            break;
        case 2:
            second = new AIPlayer(whitePlayer);
            break;
    }
    //create a game object and give it a board, players and a logic to play by.
    Game *g = new LocalGame(size, gameLogic, first, second);
	printer->startGameMessage();
	g->runGame();
    delete printer;
    delete g;
	return 0;
}