/* 
 * File:   CircleAndLegDetection.h
 * Author: gustavo
 *
 * Created on June 12, 2013, 8:42 AM
 */

#ifndef CIRCLEANDLEGDETECTION_H
#define	CIRCLEANDLEGDETECTION_H

#include "PointAndVector.h"
#include <vector>

class CircleAndLegDetection {
public:
    CircleAndLegDetection();
    virtual ~CircleAndLegDetection();
    
//    void calculateStdDev();
    
    /* For legs*/
    Point<double>* getCenters();
    void setCenters(Point<double> C1, Point<double> C2);
    void setLMosts(Point<double> l_most1, Point<double> l_most2);
    void setRMosts(Point<double> r_most1, Point<double> r_most2);

    /* For circles */
    Point<double> getCenter();
    void setCenter(Point<double> C1);
    void setLMostAndRMost(Point<double> l_most, Point<double> r_most);

private:
    Point<double> center1; // data from the 1st circle
    double radius1;
    Point<double> lMost1, rMost2; // 1st and last pointer laser scan
    Vector<double> stdDev1; /* standard Deviation about the points collected
                                           by the sensor */
    Point<double> center2; // data from the 2nd circle
    double radius2;
    Point<double> lMost2, rMost2;
    Vector<double> stdDev2;

};

#endif	/* CIRCLEANDLEGDETECTION_H */

