/* 
 * File:   MotionDetection.cpp
 * Author: gustavo
 * 
 * Created on June 12, 2013, 10:50 AM
 */

#include "MotionDetection.h"
#include "Robot.h"

MotionDetection::MotionDetection(Robot* owner) {
    if (owner != NULL) {
        m_pOwner = owner;
        o_cMatrix = Matrix(N_BOX, 2 * N_BOX);
        o_pMatrix = Matrix(N_BOX, 2 * N_BOX);

        // this->lastSeenMatrix = NULL;         precisamos fazer isso, mas como?

        o_cMatrix.Clean();
        //for (int i = 0; i <= 5; i++) { // start in the occupation for 5 times
        m_pOwner->ReadSensors();
        startOccupationMatrix();
        //}
    }
}

MotionDetection::~MotionDetection() {
}

void MotionDetection::startOccupationMatrix() {
    Point<double> P;
    for (int i = 0; i < THETA_MAX + 1; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= 3.0) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(m_pOwner->GetRange(i), i);
            int indexx = (int) (P.getX() / BOXX);
            int indexy = (int) (P.getY() / BOXY);
            /* para todos os raios frontais (um metro pra esquera e um para a direita do robo)
               digo que valem 5 (para informar que é o objeto a ser seguido).
             */
            if (indexx <= (N_BOX + (int) (N_BOX / LENGTH)) || indexx >= (N_BOX - (int) (N_BOX / LENGTH))) {
                o_cMatrix(indexx, indexy) = 5; // the frontal object to follow
            } else {
                if (m_pOwner->GetRange(i) < 3) {
                    o_cMatrix(indexx, indexy) = -1; // obstacle of ambient
                }
            }
        }
    }
}

void MotionDetection::doOccupationMatrix() {
    Point<double> P;
    Matrix newMatrix;
    newMatrix = Matrix(N_BOX, 2 * N_BOX);

    saveOccupationMatrix(); // saving actual informations

    for (int i = 0; i < THETA_MAX + 1; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= 3.0) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(m_pOwner->GetRange(i), i);
            int indexx = (int) (P.getX() / BOXX);
            int indexy = (int) (P.getY() / BOXY);
            if (m_pOwner->GetRange(i) < 3) // new tracking... all itens detected are obstacle
                newMatrix(indexx, indexy) = -1; // obstacle of ambient
        }
    }

    o_cMatrix.Clean(); // limpo a matriz

    // mapping new itens with respect of previous matrix 
    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            // obstacle turn to available
            if (o_pMatrix(i, j) == -1 && newMatrix(i, j) == 0) {
                o_cMatrix(i, j) = 0;
            }
            // obstacle turn to intended object or this object is hidden now?
            if (o_pMatrix(i, j) == -1 && newMatrix(i, j) == -1) {
                o_cMatrix(i, j) = -1; // not cheatting. 5 or -1?
            }
            // available space turn to available
            if (o_pMatrix(i, j) == 0 && newMatrix(i, j) == 0) {
                o_cMatrix(i, j) = 0;
            }
            // available space turn to obstacle
            if (o_pMatrix(i, j) == 0 && newMatrix(i, j) == -1) {
                o_cMatrix(i, j) = -1;
            }
            // intended object turn to available 
            if (o_pMatrix(i, j) == 5 && newMatrix(i, j) == 0) {
                o_cMatrix(i, j) = 0;
            }
            // intended object turn to obstacle? maybe
            if (o_pMatrix(i, j) == 5 && newMatrix(i, j) == -1) {
                o_cMatrix(i, j) = 5;
            }
        }
    }
}

int MotionDetection::getAngleToTurn() {
    this->saveOccupationMatrix();
    this->doOccupationMatrix();

    // apply difference to see how much robot need to turn
    Matrix diff = o_cMatrix - o_pMatrix;

    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            if (diff(i, j) < -4) // there is a movement
                return (BOXX - j);
        }
    }

    return 0; // there isn't movement
}

void MotionDetection::saveOccupationMatrix() {
    o_pMatrix = o_cMatrix;
}

void MotionDetection::saveLastSeenPosition() {
    lastSeenMatrix = o_cMatrix;
}

void MotionDetection::reachLastSeenPosition() {
    o_cMatrix = lastSeenMatrix;
}

/* Verifico se na matriz não tenho mais elementos > 5
   se isso ocorre, é porque o objeto a ser perseguido
   foi perdido. Retorna true para isso.
 */
bool MotionDetection::itDisapear() {
    for (int i = 0; i < N_BOX; i++) {
        for (int j = 0; j < 2 * N_BOX; j++) {
            if (o_cMatrix(i, j) > 3)
                return false;
        }
    }
    return true;
}

bool MotionDetection::isNotNullLastSeenMatrix() {
    //return lastSeenMatrix != NULL; // precisamos refazer isso.
    return false;
}
