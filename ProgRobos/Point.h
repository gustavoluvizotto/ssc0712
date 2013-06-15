/* 
 * File:   Vector.h
 * Author: gustavo
 *
 * Created on June 11, 2013, 10:46 PM
 */

#ifndef POINT_H
#define	POINT_H

#include <math.h>
#include <vector>

template <class g_Type>
class Point {
private:
    g_Type x, y;

public:
    Point() {}
    Point(g_Type x, g_Type y) {
        this->x = x;
        this->y = y;
    }

    void setX(g_Type x) {
        this->x = x;
    }

    void setY(g_Type y) {
        this->y = y;
    }

    g_Type getX() {
        return this->x;
    }

    g_Type getY() {
        return this->y;
    }

    void polarToCartesian(g_Type radius, g_Type angle) { // angle in degree.
        this->x = radius * cos(angle * M_1_PI / 180.0f);
        this->y = radius * sin(angle);
    }

    g_Type distance(g_Type x2, g_Type x1) {
        return x2 - x1;
    }
};

#endif	/* POINT_H */
