/* 
 * File:   MotionDetection.cpp
 * Author: gustavo
 * 
 * Created on June 12, 2013, 10:50 AM
 */

#include "MotionDetection.h"

MotionDetection::MotionDetection() {
}

MotionDetection::~MotionDetection() {
}

void MotionDetection::calculateMinAndMax(RangerProxy* rp, int thetai, int thetaf) {
    int thetamax = thetai;
    int thetamin = thetai;
    
    for (int i = thetai + 1; i <= thetaf; i++) {
        if ((*rp)[i] > max)
            thetamax = i;
        if ((*rp)[i] < min)
            thetamin = i;
    }
    
    Pmax.polarToCartesian((*rp)[thetamax], thetamax);
    Pmin.polarToCartesian((*rp)[thetamin], thetamin);
}

Point<double> MotionDetection::getPmax() {
    return this->Pmax;
}

Point<double> MotionDetection::getPmin() {
    return this->Pmin;
}

void MotionDetection::setPmax(double x, double y) {
    this->Pmax.setX(x);
    this->Pmax.setY(y);
}

void MotionDetection::setPmin(double x, double y) {
    this->Pmin.setX(x);
    this->Pmin.setY(y);
}