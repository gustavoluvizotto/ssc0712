/* 
 * File:   MotionDetection.h
 * Author: gustavo
 *
 * Created on June 12, 2013, 10:50 AM
 */

#ifndef MOTIONDETECTION_H
#define	MOTIONDETECTION_H

#define BOXX 0.15f      // delta_x = 15cm
#define BOXY 0.15f      // delta_y = 15cm
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
    bool isNearToPreviousObjective(const int r, const int c) const;
    int getXMin() const;
    int getXMax() const;
private:
    int threshold; // garante um número máximo de 5's
    Robot* m_pOwner;
    Matrix o_cMatrix;   //current Matrix
    Matrix o_pMatrix;   //previous Matrix
    Matrix lastSeenMatrix;
};

#endif	/* MOTIONDETECTION_H */