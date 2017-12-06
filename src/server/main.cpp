// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include <string>
#include "Server.h"

using namespace std;

#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    Server server(8000);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    server.stop();
}