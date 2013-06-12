/* 
 * File:   Vector.h
 * Author: gustavo
 *
 * Created on June 11, 2013, 10:46 PM
 */

#ifndef POINT_H
#define	POINT_H

#include <math.h>

template <typename g_Type>
class Point {
private:
    g_Type x, y;

public:

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

//#ifndef VECTOR_H
//#define VECTOR_H
//
//template <typename g_Type2>
//class Vector {
//private:
//    Point<g_Type2> p1, p2, p3;
//    Point<g_Type2> vector1, vector2;
//public:
//
//    Vector(g_Type2 point1, g_Type2 point2, g_Type2 point3) {
//        this->p1 = point1;
//        this->p2 = point2;
//        this->p3 = point3;
//        this->vector1 = point2 - point1;
//        this->vector2 = point3 - point1;
//    }
//
//    double getAngleBetweenVectors() { // between the 2 vectors atributes
//        double theta;
//        g_Type2 v1Scalar, v2Scalar;
//        v1Scalar = this->getNorma(this->vector1);
//        v2Scalar = this->getNorma(this->vector2);
//        theta = acos((double)(dotProduct()/(v1Scalar*v2Scalar)));
//        return theta;
//    }
//
//    g_Type2 dotProduct() {
//        return (this->vector1.getX() * this->vector2.getX() +
//                this->vector1.getY() * this->vector2.getY());
//    }
//
//    g_Type2 getNorma(g_Type2 vector) {  // it'll be a Point vector...
//        return sqrt(pow(vector.getX(), 2) + pow(vector.getY(), 2));
//    }
//};
//
//#endif  /* VECTOR_H */