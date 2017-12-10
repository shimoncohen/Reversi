//
// Created by shimon on 12/3/17.
//

#ifndef ADVANCEDPROGRAMMING1_SERVER_H
#define ADVANCEDPROGRAMMING1_SERVER_H

#include <string>
using namespace std;

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket;
    int handleClient(int clientSocket, int *x, int *y);
    int writeToClient(int clientSocket, int *x, int *y);
};

#endif //ADVANCEDPROGRAMMING1_SERVER_H
