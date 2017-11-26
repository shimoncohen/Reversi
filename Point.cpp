//
// Created by shimon on 11/2/17.
//

#include "Point.h"

Point::Point(int x1, int y1) {
    x = x1;
    y = y1;
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