/* 
 * File:   CollisionAvoidance.h
 * Author: gustavo
 *
 * Created on June 26, 2013, 11:14 AM
 */

#ifndef COLLISIONAVOIDANCE_H
#define	COLLISIONAVOIDANCE_H

#include "Matrix.h"
#include "Point.h"
#include "Robot.h"

class CollisionAvoidance {
public:
    CollisionAvoidance(const Matrix& M, Robot* owner);
    virtual ~CollisionAvoidance();
    bool willCollideWithObjective();
    bool willCollideWithObstacle();
    bool isCriticalLevel(const int ref);
    int getYMin(const int ref);
    int getYMax(const int ref);
    int getXMin(const int ref);
    int getXMax(const int ref);
    double decreaseSpeed(double actualSpeed);
    double getAngleToAvoid(Robot* owner);
private:
    Matrix m_cMatrix;
};

#endif	/* COLLISIONAVOIDANCE_H */

