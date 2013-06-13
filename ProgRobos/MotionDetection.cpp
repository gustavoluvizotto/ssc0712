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
    this->disapear = false;
    this->lastSeenMatrix = NULL;
}

MotionDetection::~MotionDetection() {
    delete this->o_cMatrix;
    delete this->o_pMatrix;
}

void MotionDetection::startOccupationMatrix(RangerProxy* rp) {
    Point<double> P;
    for (int i = 0; i < THETA_MAX + 1; i++) { // para todos os angulos
        if (rp->GetRange(i) <= 3.0) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(rp->GetRange(i), i);
            int indexx = (int) (P.getX() / BOXX); 
            int indexy = (int) (P.getY() / BOXY);
            /* para todos os raios frontais (um metro pra esquera e um para a direita do robo)
               digo que valem 5 (para informar que é o objeto a ser seguido).
            */
            if (indexx <= (N_BOX + (int) (N_BOX / LENGTH)) || indexx >= (N_BOX - (int) (N_BOX / LENGTH)))
                this->o_cMatrix[indexx][indexy] = 5; // the frontal object to follow
            if (rp->GetRange(i) < 3)
                this->o_cMatrix[indexx][indexy] = -1; // obstacle of ambient
        }
    }
}

int MotionDetection::getAngleToTurn(RangerProxy* rp) {
    int** diff;

    this->saveOccupationMatrix();
    this->startOccupationMatrix(RangerProxy * rp);

    diff = this->o_cMatrix - this->o_pMatrix;
    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            if (diff[i][j] < -4) // there is a movement
                return (BOXX - j);
        }
    }
    return 0.0; // there isn't movement
}

void MotionDetection::saveOccupationMatrix() {
    this->o_pMatrix = this->o_cMatrix;
}

void MotionDetection::saveLastSeenPosition() {
    if (this->itDisapear())
        this->lastSeenMatrix = this->o_cMatrix;
}

void MotionDetection::reachLastSeenPosition() {
    this->o_cMatrix = this->lastSeenMatrix;
}

