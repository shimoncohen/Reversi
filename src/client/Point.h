// 315383133 shimon cohen
// 302228275 Nadav Spitzer

#ifndef EX1_POINT_H
#define EX1_POINT_H

/*
 * A point consisting x and y values.
 */
class Point {
private:
    int x;
    int y;
public:
    /*
	 * function name: Point.
	 * input: two numbers as coordinate.
	 * output: none.
     * operation: constructor.
    */
    Point(int x1, int y1);
    /*
	 * function name: ~Point.
	 * input: none.
	 * output: none.
     * operation: destructor.
    */
    ~Point();
    /*
	 * function name: getPoint.
	 * input: none.
	 * output: an array of ints.
     * operation: returnes the points x and y values.
    */
    int *getPoint();

    /*
	 * function name: getX.
	 * input: none.
	 * output: the points x value.
     * operation: returnes the points x value.
    */
    int getX();

    /*
	 * function name: getY.
	 * input: none.
	 * output: the points y value.
     * operation: returnes the points y value.
    */
    int getY();
    /*
	 * function name: operator ==.
	 * input: two Point objects.
	 * output: a boolean value indicating if Points are equal.
     * operation: returns 1 if points are equal, 0 otherwise.
    */
    friend bool operator ==(Point &point1, Point &point2);
};


#endif //EX1_POINT_H
