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

#include "Robot.h"
#include "Point.h"

using namespace std;
using namespace PlayerCc;

class MotionDetection {
public:
    MotionDetection();
    virtual ~MotionDetection();
    void startOccupationMatrix(RangerProxy* rp);// initial condition  
    int getAngleToTurn(RangerProxy* rp);        // called all time
    void saveOccupationMatrix();
    void saveLastSeenPosition();
    void reachLastSeenPosition();
    bool itDisapear();
    void doOccupationMatrix(RangerProxy* rp);   // when following
    void zeros(int** M);
    int** operator +(int** M1, int** M2);   // operators to do maths with
    int** operator -(int** M1, int** M2);   // matrix
    int** operator =(int** M1, int** M2);
private:
    int** o_cMatrix;       // current occupation Matrix
    int** o_pMatrix;       // previous occupation Matrix
    int** lastSeenMatrix;
};

#endif	/* MOTIONDETECTION_H */

