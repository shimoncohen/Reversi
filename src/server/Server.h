//
// Created by shimon on 12/3/17.
//

#ifndef ADVANCEDPROGRAMMING1_SERVER_H
#define ADVANCEDPROGRAMMING1_SERVER_H

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket;
    void handleClient(int firstClientSocket, int secondClientSocket);
    int calc(int arg1, const char op, int arg2) const;
};

#endif //ADVANCEDPROGRAMMING1_SERVER_H
