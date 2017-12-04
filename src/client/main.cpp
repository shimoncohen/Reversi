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
    while(choice != 1 && choice != 2 && choice != 3) {
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
    Player *first;
    Player *second;
    Game *g;
    // creating the second player according to the game style (Player/ AI).
    // create a game object and give it a board, players and a logic to play by.
    switch(choice) {
        case 1:
            first = new HumanPlayer(blackPlayer);
            second = new HumanPlayer(whitePlayer);
            g = new LocalGame(size, gameLogic, first, second);
            break;
        case 2:
            first = new HumanPlayer(blackPlayer);
            second = new AIPlayer(whitePlayer);
            g = new LocalGame(size, gameLogic, first, second);
            break;
        case 3:
            first = new ServerPlayer("127.0.0.1", 8000, blackPlayer);
            second = new ServerPlayer("127.0.0.1", 8000, whitePlayer);
            g = new ServerGame(size, gameLogic, first);
    }

	printer->startGameMessage();
	g->runGame();
    delete printer;
    delete g;
	return 0;
}