/*shimon cohen*/
/*315383133*/

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
	 * input: none.
	 * output: none.
     * operation: constructor.
    */
    Point(int x1, int y1);
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
};


#endif //EX1_POINT_H
