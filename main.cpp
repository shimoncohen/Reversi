/*shimon cohen*/
/*315383133*/

#include "Game.h"

int main() {
    int size, choice = 0;
    cout << "Reversi!" << endl << "Welcome to the game menu" << endl << "which mode would you like to play?" << endl;
    cout << "1) Player VS Player" << endl << "2) Player VS Computer(AI)" << endl;
    cin >> choice;
    while(choice != 1 && choice != 2) {
        cout << "Invalid option." << endl << endl;
        cout << "which mode would you like to play?" << endl;
        cout << "1) Player VS Player" << endl << "2) Player VS Computer(AI)" << endl;
        cin >> choice;
    }
    cout << "Please insert board size (must be greater than or equal to four):" << endl;
    cin >> size;
    while(size < 4) {
        cout << "Please insert a valid board size (must be greater than or equal to four):" << endl;
        cin >> size;
    }
//    while(size < 4 || size % 2 == 1) {
//        cout << "Please insert a valid board size (must be an even number greater than zero):" << endl;
//        cin >> size;
//    }
    GameLogic* gameLogic = new StandartGameLogic();
    Player *first = new HumanPlayer(black);
    Player *second;
    switch(choice) {
        case 1:
            second = new HumanPlayer(white);
            break;
        case 2:
            second = new AIPlayer(white);
            break;
    }
    Game g(size, gameLogic, first, second);//create a game object and give it a board, players and a logic to play by.
    cout << "Start game!" << endl;
    g.runGame();
    return 0;
}