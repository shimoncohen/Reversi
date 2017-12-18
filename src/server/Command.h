// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef ADVANCEDPROGRAMMING1_COMMAND_H
#define ADVANCEDPROGRAMMING1_COMMAND_H

#include <vector>
#include "iostream"
using namespace std;

class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
};

#endif //ADVANCEDPROGRAMMING1_COMMAND_H
