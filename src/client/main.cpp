// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "LocalGame.h"
#include <fstream>
#include <stdlib.h>
#include <string.h>
#define ENDPORTWORD 5
#define ENDIPWORD 3

using namespace std;

void settingsReading(int* port, char *IPAddress);

int main() {
    char *IPAddress = (char*)malloc(255 * sizeof(char));
	int size, choice = 0, port;
    settingsReading(&port, IPAddress);
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
            first = new HumanPlayer();
            second = new HumanPlayer();
            g = new LocalGame(size, gameLogic, first, second);
            break;
        case 2:
            first = new HumanPlayer();
            second = new AIPlayer();
            g = new LocalGame(size, gameLogic, first, second);
            break;
        case 3:
            first = new HumanPlayer();
            second = new ServerPlayer(IPAddress, port);
            g = new LocalGame(size, gameLogic, first, second);
    }
	g->runGame();
    delete printer;
    delete g;
	return 0;
}

/*
    * function name: settingsReading.
    * input: int* port, const char** IPAddress.
    * output: none.
    * operation: reads the port number, and IP address of the server from a file.
*/
void settingsReading(int* port, char *IPAddress) {
    //reader for the file
    string reader;
    //input streamer
    ifstream serverInfo;
    serverInfo.open("serverInfo.txt", ios::in);
    //error opening file will give a proper message
    if(!serverInfo.is_open()) {
        cout << "Error reading from file" << endl;
        //file opening was succssesful
    } else {
        //reading from the file
        while(!serverInfo.eof()) {
            serverInfo >> reader;
            if(reader.find("IP:", 0) == 0) {
                //removing "IP:" from the string
                reader = reader.erase(0, ENDIPWORD);
                strcpy(IPAddress, reader.c_str());
            } else if(reader.find("Port:", 0) == 0) {
                //removing "Port:" from the string
                reader = reader.erase(0, ENDPORTWORD);
                //converting to int
                *port = atoi(reader.c_str());
            }
        }
    }
    serverInfo.close();
}