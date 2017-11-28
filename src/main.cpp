// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Game.h"

int main() {
	int size, choice = 0;
    cout << "Reversi!" << endl << "Welcome to the game menu" << endl << "which mode would you like to play?" << endl;
    cout << "1) Player VS Player" << endl << "2) Player VS Computer(AI)" << endl;
    // choosing game style. 1) PvP . 2) PvAI.
    cin >> choice;
    // dealing with impossible option
    while(choice != 1 && choice != 2) {
        cout << "Invalid option." << endl << endl;
        cout << "which mode would you like to play?" << endl;
        cout << "1) Player VS Player" << endl << "2) Player VS Computer(AI)" << endl;
        cin >> choice;
    }
    // getting board size from the user
    cout << "Please insert board size (must be greater than or equal to four):" << endl;
    cin >> size;
    //dealing with size < 4
	while(size < 4) {
        cout << "Please insert a valid board size (must be greater than or equal to four):" << endl;
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
    Game g(size, gameLogic, first, second);
	cout << "Start game!" << endl;
	g.runGame();
	return 0;
}