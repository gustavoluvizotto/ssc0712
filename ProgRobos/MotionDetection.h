/* 
 * File:   MotionDetection.h
 * Author: gustavo
 *
 * Created on June 12, 2013, 10:50 AM
 */

#ifndef MOTIONDETECTION_H
#define	MOTIONDETECTION_H

#include <libplayerc++/playerc++.h>
#include "PointAndVector.h"

using namespace PlayerCc;

class MotionDetection {
public:
    MotionDetection();
    virtual ~MotionDetection();

    void calculateMinAndMax(RangerProxy* rp, int thetai, int thetaf);
    
    Point<double> getPmin();
    void setPmin(double x, double y);
    Point<double> getPmax();
    void setPmax(double x, double y);

private:
    Point<double> Pmin, Pmax;
};

#endif	/* MOTIONDETECTION_H */

