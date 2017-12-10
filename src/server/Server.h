// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_SERVER_H
#define ADVANCEDPROGRAMMING1_SERVER_H

#include <string>
using namespace std;

class Server {
public:
    /*
	 * function name: Server.
	 * input: gets the number of the port the server listens to.
	 * output: none.
     * operation: constructor.
    */
    Server(int port);
    /*
	 * function name: start.
	 * input: none.
	 * output: none.
     * operation: Starts the server's activity.
    */
    void start();
    /*
	 * function name: stop.
	 * input: none.
	 * output: none.
     * operation: Stops the server's activity.
    */
    void stop();
private:
    int port;
    int serverSocket;
    /*
	 * function name: handleClient.
	 * input: gets socket number to read the player's move from, and a point as x and y.
	 * output: Returns 1 if player disconnected, and 0 otherwise.
     * operation: Reads the values of the point from the socket and assign them to x and y .
    */
    int handleClient(int clientSocket, int *x, int *y);
    /*
	 * function name: writeToClient .
	 * input: gets socket number to write the player's move into, and a point as x and y.
	 * output: Returns 1 if player disconnected, and 0 otherwise.
     * operation: Writes the values of the point into the socket by receiving them as x and y .
    */
    int writeToClient(int clientSocket, int *x, int *y);
};

#endif //ADVANCEDPROGRAMMING1_SERVER_H
