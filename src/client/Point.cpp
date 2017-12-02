// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#include "Point.h"

Point::Point(int x1, int y1) {
    x = x1;
    y = y1;
}

Point::~Point() {

}

int* Point::getPoint() {
    int* temp = new int[2];
    temp[0] = x;
    temp[1] = y;
    return temp;
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

bool operator ==(Point &board1, Point &board2) {
    if(board1.getX() == board2.getX() && board1.getY() == board2.getY()) {
        return true;
    }
    return false;
}