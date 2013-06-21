/* 
 * File:   MotionDetection.h
 * Author: gustavo
 *
 * Created on June 12, 2013, 10:50 AM
 */

#ifndef MOTIONDETECTION_H
#define	MOTIONDETECTION_H

#define BOXX 0.15f      // delta_x
#define BOXY 0.15f      // delta_y
#define N_BOX 20        // number of boxes in an axis

#include "Point.h"
#include "Matrix.h"

class Robot;

using namespace std;

class MotionDetection {
public:
    MotionDetection(Robot* owner);
    virtual ~MotionDetection();
    void startOccupationMatrix();// initial condition  
    int getAngleToTurn();        // called all time
    void saveOccupationMatrix();
    void saveLastSeenPosition();
    void reachLastSeenPosition();
    bool itDisapear();
    void doOccupationMatrix();   // when following
    bool isNotNullLastSeenMatrix();
private:
    Robot* m_pOwner;
    Matrix o_cMatrix;
    Matrix o_pMatrix;
    Matrix lastSeenMatrix;
};

#endif	/* MOTIONDETECTION_H */