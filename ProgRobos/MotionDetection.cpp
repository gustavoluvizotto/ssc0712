/* 
 * File:   MotionDetection.cpp
 * Author: gustavo
 * 
 * Created on June 12, 2013, 10:50 AM
 */

#include "MotionDetection.h"

MotionDetection::MotionDetection() {
    this->o_cMatrix = new int* [N_BOX];
    this->o_pMatrix = new int* [N_BOX];

    for (int i = 0; i < N_BOX; i++) {
        this->o_cMatrix[i] = new int [2 * N_BOX];
        this->o_pMatrix[i] = new int [2 * N_BOX];
    }

    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            this->o_cMatrix[i][j] = 0.0;
            this->o_pMatrix[i][j] = 0.0;
        }
    }
}

MotionDetection::~MotionDetection() {
    delete this->o_cMatrix;
    delete this->o_pMatrix;
}

void MotionDetection::startOccupationMatrix(RangerProxy* rp) {
    Point<double> P;
    for (int i = 0; i < THETA_MAX + 1; i++) {
        if ((*rp)[i] <= 3.0) {
            P.polarToCartesian((*rp), i);
            int indexx = (int) P.getX() / BOXX;
            int indexy = (int) P.getY() / BOXY;
            if (indexx <= (N_BOX + (int) (N_BOX / LENGTH)) || indexx >= (N_BOX - (int) (N_BOX / LENGTH)))
                this->o_cMatrix[indexx][indexy] = 5; // the frontal object to follow
            if ((*rp)[i] < 3)
                this->o_cMatrix[indexx][indexy] = -1; // obstacle of ambient
        }
    }
}

int MotionDetection::getAngleToTurn(RangerProxy* rp) {
    int** diff;
    this->o_pMatrix = this->o_cMatrix;
    this->startOccupationMatrix(RangerProxy * rp);

    diff = this->o_cMatrix - this->o_pMatrix;
    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            if (diff[i][j] < -4)       // there is a movement
                return (BOXX - j);
        }
    }
    return 0.0; // there isn't movement
}

//void MotionDetection::calculateMinAndMax(RangerProxy* rp, int thetai, int thetaf) {
//    int thetamax = thetai;
//    int thetamin = thetai;
//    for (int i = thetai + 1; i <= thetaf; i++) {
//        if ((*rp)[i] > max)
//            thetamax = i;
//        if ((*rp)[i] < min)
//            thetamin = i;
//    }
//    Pmax.polarToCartesian((*rp)[thetamax], thetamax);
//    Pmin.polarToCartesian((*rp)[thetamin], thetamin);
//}
//Point<double> MotionDetection::getPmax() {
//    return this->Pmax;
//}
//Point<double> MotionDetection::getPmin() {
//    return this->Pmin;
//}
//void MotionDetection::setPmax(double x, double y) {
//    this->Pmax.setX(x);
//    this->Pmax.setY(y);
//}
//void MotionDetection::setPmin(double x, double y) {
//    this->Pmin.setX(x);
//    this->Pmin.setY(y);
//}