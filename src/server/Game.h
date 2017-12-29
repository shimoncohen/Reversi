// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_GAME_H
#define ADVANCEDPROGRAMMING1_GAME_H

#include <sys/socket.h>
#include <string>

using namespace std;

class Game {
public:
    /*
	 * function name: Game.
	 * input: a string of he game's name, 2 numbers as the sockets of both players.
	 * output: none.
     * operation: constructor.
    */
    Game(string gameName, int socket1, int socket2);
    /*
	 * function name: getName.
	 * input: none.
	 * output: a string of the current game's name.
     * operation: returns the name of the current game as a string.
    */
    string getName();
    /*
	 * function name: getStatus.
	 * input: none.
	 * output: true if the game is active, false if the game is waiting.
     * operation: returns the current  activation status of the game.
    */
    bool getStatus();
    /*
	 * function name: getFirstPlayer.
	 * input: none.
	 * output: the socket number.
     * operation: returns the socket number of the first player.
    */
    int getFirstPlayer();
    /*
	 * function name: getSecondPlayer.
	 * input: none.
	 * output: the socket number.
     * operation: returns the socket number of the second player.
    */
    int getSecondPlayer();
    /*
	 * function name: getThread.
	 * input: none.
	 * output: the thread number.
     * operation: returns the thread of the current running game.
    */
    pthread_t getThread();
    /*
	 * function name: joinGame.
	 * input: a socket number of the newPlayer.
	 * output: none.
     * operation: sets the socket of the second player, and changes the status of the game to TRUE.
    */
    void joinGame(int newPlayer);
    /*
	 * function name: setThread.
	 * input: a thread number.
	 * output: none.
     * operation: sets the variable gamesThread as the given thread .
    */
    void setThread(pthread_t newGameThread);
private:
    string name;
    int firstPlayerSocket;
    int secondPlayerSocket;
    bool status;
    pthread_t gamesThread;
};


#endif //ADVANCEDPROGRAMMING1_GAME_H
