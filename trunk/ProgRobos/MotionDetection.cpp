/* 
 * File:   MotionDetection.cpp
 * Author: gustavo
 * 
 * Created on June 12, 2013, 10:50 AM
 */

#include "MotionDetection.h"
#include "Robot.h"
#include <cmath>

MotionDetection::MotionDetection(Robot* owner) {
    if (owner != NULL) {
        threshold = 0;
        m_pOwner = owner;
        o_cMatrix = Matrix(N_BOX, 2 * N_BOX); //já cria com zeros
        o_pMatrix = Matrix(N_BOX, 2 * N_BOX); //já cria com zeros

        for (int i = 0; i <= 5; i++)
            m_pOwner->ReadSensors(); //cria um delay. Bug do PlayerCC
        startOccupationMatrix();
    }
}

MotionDetection::~MotionDetection() {
}

void MotionDetection::startOccupationMatrix() {
    Point<double> P;
    int x, y;

    for (int i = 0; i < THETA_MAX; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= LENGTH) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(m_pOwner->GetRange(i), i);
            y = ceil(P.getY() / BOXY);
            if (y > N_BOX) y = N_BOX;
            if (y == 0) y = 1;
            x = N_BOX + ceil(P.getX() / BOXX);
            if (x > N_BOX) x = N_BOX;
            if (x == 0) x = 1;

            /* para todos os raios frontais (um metro pra esquera e um para a direita do robo)
               digo que valem 5 (para informar que é o objeto a ser seguido).
             */
            if (x <= (N_BOX + (int) (N_BOX / LENGTH)) || x >= (N_BOX - (int) (N_BOX / LENGTH))) {
                o_cMatrix(y, x) = 5; // the frontal object to follow
                threshold++;
            } else {
                if (m_pOwner->GetRange(i) < LENGTH) {
                    o_cMatrix(y, x) = -1; // obstacle of ambient
                }
            }
        }
    }
    o_cMatrix.Print();
}

void MotionDetection::doOccupationMatrix() {
    int nfives = 0;
    Point<double> P;
    //    Matrix newMatrix = Matrix(N_BOX, 2 * N_BOX);
    int x, y;

    saveOccupationMatrix(); // saving actual informations

    o_cMatrix.Clean(); // limpo a matriz

    for (int i = 0; i < THETA_MAX; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= LENGTH) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(m_pOwner->GetRange(i), i);
            x = N_BOX + (int) (P.getX() / BOXX);
            y = 1 + (int) (P.getY() / BOXY);
            if (m_pOwner->GetRange(i) < LENGTH && x >= 1 && y >= 1) {// new tracking... all itens detected are obstacle
                o_cMatrix(y, x) = -1; // obstacle of ambient
                if (isNearToPreviousObjective(y, x) && nfives <= threshold) {
                    o_cMatrix(y, x) = 5;
                    nfives++;
                }
            }
        }
    }

    /*
        // mapping new itens with respect of previous matrix 
        for (int i = 1; i < N_BOX; i++) {
            for (int j = 1; j < 2 * N_BOX; j++) {
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
     */

    o_cMatrix.Print();
}

//percorre procurando se tem algum 5 ao redor de i,j

bool MotionDetection::isNearToPreviousObjective(const int r, const int c) const {
    for (int k = -1; k <= 1; k++)
        for (int l = -1; l <= 1; l++) {
            if (r + k >= 1 && c + l >= 1) // nao acesso indices nao definidos
                if (o_pMatrix.get(r + k, c + l) == 5)
                    return true;
        }
    return false;
}

int MotionDetection::getAngleToTurn() {
    this->saveOccupationMatrix();
    this->doOccupationMatrix();

    // apply difference to see how much robot need to turn
    Matrix diff = o_cMatrix - o_pMatrix;

    for (int i = 1; i < N_BOX; i++) {
        for (int j = 1; j < 2 * N_BOX; j++) {
            if (diff(i, j) < -4) // there is a movement
                return (BOXX - j) / 10.0; //Guba, dividi por 10 pra girar mais devagar, mas nem testei.
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
    for (int i = 1; i <= N_BOX; i++) {
        for (int j = 1; j <= 2 * N_BOX; j++) {
            if (o_cMatrix(i, j) > 3)
                return false;
        }
    }
    return true;
}

/**
 * 
 * @return true se a matriz já foi alocada. false caso contrário.
 */
bool MotionDetection::isNotNullLastSeenMatrix() {
    return lastSeenMatrix.isAllocated();
}
