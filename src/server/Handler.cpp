//
// Created by shimon on 12/23/17.
//

#include "Handler.h"

//Handler::Handler(Server server) : serverToHandle(server) {
//
//}

//void* Handler::handleClient(void* socket) {
//    CommandsManager cm;
//    CommandAndArgs commandAndArgs;
//    //vector<string> tempArguments;
//    char buffer[BUFFERSIZE];
//    string command, arguments[SECOND];
//    int i = 0, args = 0;
//    int n = read(*((int*)socket), buffer, BUFFERSIZE*sizeof(char));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return NULL;
//    }
//    if (n == 0) {
//        cout << "Client disconnected" << endl;
//        return NULL;
//    }
////    for(i; i < BUFFERSIZE; i++) {
////        if(buffer[i] != '\0') {
////            if(buffer[i] != " ") {
////                command.append(buffer[i]);
////                //command = command + buffer[i];
////            } else {
////                break;
////            }
////        } else {
////            break;
////        }
////    }
////    for(i; i < BUFFERSIZE; i++) {
////        if(buffer[i] != '\0') {
////            if(buffer[i] != " ") {
////                arguments->append(buffer[i]);
////                //arguments[args] = arguments[args] + buffer[i];
////            } else {
////                args += 1;
////            }
////        } else {
////            break;
////        }
////    }
////    if(args == 1) {
////        tempArguments.push_back(arguments[0]);
////    }
////    if(args == 2) {
////        tempArguments.push_back(arguments[1]);
////    }
//    commandAndArgs = extractCommandAndArgs(buffer);
//    cm.executeCommand(commandAndArgs.command, commandAndArgs.args, games, *((int*)socket));
////    int playerNum = FIRST;
////    int n = write((int)socket, &playerNum, sizeof(playerNum));
////    if (n == -1) {
////        cout << "Error writing to socket" << endl;
////        return NULL;
////    }
////    cout << "First player connected" << endl;
////    if ((int)socket == -1)
////        throw "Error on accept";
//}
//
//void* Handler::handleGame(void* gameToHandle) {
//    CommandsManager cm;
//    CommandAndArgs commandAndArgs;
//    //vector<string> arguments;
//    int n, temp;
//    //int x = 0, y = 0, temp;
//    //int i = 0, tempX = 0, tempY = 0, flag = 0;
//    string startMessage = STARTMESSAGE;
//    char buffer[BUFFERSIZE];
//    Game *currentGame = (Game*)gameToHandle;
//    n = write(currentGame->getFirstPlayer(), &startMessage, sizeof(startMessage));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return NULL;
//    }
//    n = write(currentGame->getSecondPlayer(), &startMessage, sizeof(startMessage));
//    if (n == -1) {
//        cout << "Error writing to socket" << endl;
//        return NULL;
//    }
//    if (currentGame->getSecondPlayer() == -1)
//        throw "Error on accept";
//    int currentClient = currentGame->getFirstPlayer();
//    int waitingClient = currentGame->getSecondPlayer();
//    //while(x != -2 || y != -2) {
//    do {
//        //read the info sent from the client.
//        int n = read(currentClient, buffer, BUFFERSIZE*sizeof(char));
//        if (n == -1) {
//            return NULL;
//        }
//        if (n == 0) {
//            cout << "Client disconnected" << endl;
//            return NULL;
//        }
////        while(buffer[i] != '\0') {
////            command.append(buffer[i]);
////            //command = command + buffer[i];
////            i++;
////        }
//        commandAndArgs = extractCommandAndArgs(buffer);
//        cm.executeCommand(commandAndArgs.command, commandAndArgs.args, games, *((int*)socket));
////        for(i; i < BUFFERSIZE && buffer[i] != '\0'; i++) {
////            if(flag == 1 && buffer[i] == ' ') {
////                flag = 2;
////            }
////            if(flag != 2 && buffer[i] >= 48 && buffer[i] <= 58) {
////                tempX *= tempX;
////                tempX += buffer[i] - 48;
////                flag = 1;
////            }
////            if(flag == 2 && buffer[i] >= 48 && buffer[i] <= 58) {
////                tempY *= tempY;
////                tempY += buffer[i] - 48;
////                flag = 1;
////            }
////        }
////        x = tempX;
////        y = tempY;
////        if(x == -1 && y == -1) {
////            cout << "Player has no move" << endl;
////        } else if(x == -2 && y == -2) {
////            cout << "Got end of game info" << endl;
////        } else {
////            cout << "Got info: " << "move " << x + 1 << " " << y + 1 << endl;
////        }
//        temp = currentClient;
//        currentClient = waitingClient;
//        waitingClient = temp;
//    } while(strcmp(commandAndArgs.command.c_str(), "End") != 0);
//
//    ///////////////send command to CM//////////////
//
//    // end of game
//    // Close communication with the client.
//    close(currentGame->getFirstPlayer());
//    close(currentGame->getSecondPlayer());
//    delete gameToHandle;
//}
//
//CommandAndArgs Handler::extractCommandAndArgs(char buffer[BUFFERSIZE]) {
//    int i = 0, args = 0;
//    string startMessage = STARTMESSAGE, command, arguments[SECOND];
//    CommandAndArgs commandAndArgs;
//    for(i; i < BUFFERSIZE; i++) {
//        if(buffer[i] != '\0') {
//            if(buffer[i] != ' ') {
//                command.append(sizeof(char) ,buffer[i]);
//                //command = command + buffer[i];
//            } else {
//                break;
//            }
//        } else {
//            break;
//        }
//    }
//    if(buffer[i] != '\0') {
//        i++;
//    }
//    for(i; i < BUFFERSIZE; i++) {
//        if(buffer[i] != '\0') {
//            if(buffer[i] != ' ') {
//                arguments[args].append(sizeof(char), buffer[i]);
//                //arguments[args] = arguments[args] + buffer[i];
//            } else {
//                args += 1;
//                i++;
//            }
//        } else {
//            break;
//        }
//    }
//    commandAndArgs.command = command;
//    if(args == 1) {
//        commandAndArgs.args.push_back(arguments[0]);
//    }
//    if(args == 2) {
//        commandAndArgs.args.push_back(arguments[1]);
//    }
//    return commandAndArgs;
//}