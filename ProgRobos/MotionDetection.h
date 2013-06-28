/* 
 * File:   MotionDetection.h
 * Author: gustavo
 *
 * Created on June 12, 2013, 10:50 AM
 */

#ifndef MOTIONDETECTION_H
#define	MOTIONDETECTION_H

#include "Parameters.h"
#include "Point.h"
#include "Matrix.h"

class Robot;

using namespace std;

class MotionDetection {
public:
    MotionDetection(Robot* owner);
    virtual ~MotionDetection();
    void startOccupationMatrix();// initial condition  
    double getAngleToTurn();        // called all time
    void saveOccupationMatrix();
    void saveLastSeenPosition();
    void reachLastSeenPosition();
    bool isProfessorHasDisappeared();
    void doOccupationMatrix();   // when following
    bool isNotNullLastSeenMatrix();
    bool isNextToFives(const Matrix&, const int row, const int col) const;
    int getXMin() const;
    int getXMax() const;
    int getXMiddle() const;
    
private:
    int threshold; // garante um número máximo de 5's
    Robot* m_pOwner;
    Matrix m_CurrentMatrix;   //current Matrix
    Matrix m_PreviousMatrix;   //previous Matrix
    Matrix m_lastSeenMatrix;
};

#endif	/* MOTIONDETECTION_H */