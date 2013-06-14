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
                o_cMatrix[indexx][indexy] = 5; // the frontal object to follow
            if (rp->GetRange(i) < 3)
                o_cMatrix[indexx][indexy] = -1; // obstacle of ambient
        }
    }
}

void MotionDetection::doOccupationMatrix(RangerProxy* rp) {
    int** newMatrix;
    Point<double> P;
    
    newMatrix = new int* [N_BOX];
    for (int i = 0; i < N_BOX; i++)
        newMatrix = new int [2 * N_BOX];

    saveOccupationMatrix();  // saving actual informations
    
    for (int i = 0; i < THETA_MAX + 1; i++) { // para todos os angulos
        if (rp->GetRange(i) <= 3.0) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(rp->GetRange(i), i);
            int indexx = (int) (P.getX() / BOXX); 
            int indexy = (int) (P.getY() / BOXY);
            if (rp->GetRange(i) < 3)    // new tracking... all itens detected are obstacle
                newMatrix[indexx][indexy] = -1; // obstacle of ambient
        }
    }

    zeros(o_cMatrix);   // clean the current matrix
    // mapping new itens with respect of previous matrix 
    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            // obstacle turn to available
            if (o_pMatrix[i][j] == -1 && newMatrix[i][j] == 0)
                o_cMatrix[i][j] = 0;
            // obstacle turn to intended object or this object is hidden now?
            if (o_pMatrix[i][j] == -1 && newMatrix[i][j] == -1)
                o_cMatrix[i][j] = -1;   // not cheatting. 5 or -1?
            // available space turn to available
            if (o_pMatrix[i][j] == 0 && newMatrix[i][j] == 0)
                o_cMatrix[i][j] = 0;
            // available space turn to obstacle
            if (o_pMatrix[i][j] == 0 && newMatrix[i][j] == -1)
                o_cMatrix[i][j] = -1;
            // intended object turn to available 
            if (o_pMatrix[i][j] == 5 && newMatrix[i][j] == 0)
                o_cMatrix[i][j] = 0;
            // intended object turn to obstacle? maybe
            if (o_pMatrix[i][j] == 5 && newMatrix[i][j] == -1)
                o_cMatrix[i][j] = 5;
        }
    }
}

void MotionDetection::zeros(int** M) {
    for (int i = 0; i < N_BOX; i++) 
        for (int j = 0; j < 2 * N_BOX; j++)
            M[i][j] = 0;
}

int MotionDetection::getAngleToTurn(RangerProxy* rp) {
    int** diff;

    this->saveOccupationMatrix();
    this->doOccupationMatrix(RangerProxy * rp);

    // apply difference to see how much robot need to turn
    diff = o_cMatrix - o_pMatrix; 

    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            if (diff[i][j] < -4) // there is a movement
                return (BOXX - j);
        }
    }
    
    return 0; // there isn't movement
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

/* Verifico se na matriz não tenho mais elementos > 5
   se isso ocorre, é porque o objeto a ser perseguido
   foi perdido. Retorna true para isso.
*/
bool MotionDetection::itDisapear() {
    if (this->o_cMatrix != NULL) {
        for (int i = 0; i < N_BOX; i++) {
            for (int j = 0; j < 2 * N_BOX; j++) {
                if (o_cMatrix[i][j] > 3) 
                    return false;
            }
        }
        return true;
    } else return false;
}

int** MotionDetection::operator +(int** M1, int** M2){
    if (M1 != NULL && M2 != NULL) {
        int** result;
        result = new int* [N_BOX];
        for (int i = 0; i < N_BOX; i++)
            result[i] = new int [2 * N_BOX];

        for (int i = 0; i < N_BOX; i++) {
           for (int j = 0; j < 2 * N_BOX; j++) {
                result[i][j] = M1[i][j] + M2[i][j]; 
            }
        }
        return result;
    } else return -1; 
}

int** MotionDetection::operator -(int** M1, int** M2){
    if (M1 != NULL && M2 != NULL) {
        int** result;
        result = new int* [N_BOX];
        for (int i = 0; i < N_BOX; i++)
            result[i] = new int [2 * N_BOX];

        for (int i = 0; i < N_BOX; i++) {
           for (int j = 0; j < 2 * N_BOX; j++) {
                result[i][j] = M1[i][j] - M2[i][j]; 
            }
        }
        return result;
    } else return -1; 
}
