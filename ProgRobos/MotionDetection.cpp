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

    for (int i = THETA_MIN; i <= THETA_MAX; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= LENGTH) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(m_pOwner->GetRange(i), i);
            y = ceil(P.getY() / BOXY);
            if (y > N_BOX) y = N_BOX;
            if (y == 0) y = 1;
            x = N_BOX + ceil(P.getX() / BOXX);
            if (x > 2 * N_BOX) x = 2 * N_BOX - 1;
            if (x == 0) x = 1;

            /* para todos os raios frontais (um metro pra esquera e um para a direita do robo)
               digo que valem 5 (para informar que é o objeto a ser seguido).
             */
            if (x <= (N_BOX + ceil(N_BOX / LENGTH)) || x >= (N_BOX - ceil(N_BOX / LENGTH))) {
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
    int x, y;

    saveOccupationMatrix(); // saving actual informations

    o_cMatrix.Clean(); // limpo a matriz

    for (int i = THETA_MIN; i <= THETA_MAX; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= LENGTH) { // para os raios que estejam dentro da caixa imaginaria
            P.polarToCartesian(m_pOwner->GetRange(i), i);
            y = ceil(P.getY() / BOXY);
            if (y > N_BOX) y = N_BOX;
            if (y == 0) y = 1;
            x = N_BOX + ceil(P.getX() / BOXX);
            if (x > 2 * N_BOX) x = 2 * N_BOX;
            if (x == 0) x = 1;

            if (m_pOwner->GetRange(i) < LENGTH) {// new tracking... all itens detected are obstacle
                o_cMatrix(y, x) = -1; // obstacle of ambient
                if (isNearToPreviousObjective(y, x) && nfives <= threshold) {
                    o_cMatrix(y, x) = 5;
                    nfives++;
                }
            }
        }
    }
    o_cMatrix.Print();
}

/**percorre procurando se tem algum 5 ao redor de i,j
 * @param linha r e coluna c
 * @return true se está nas redondezas de um 5 e false cc.
 */
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
    int jmin, jmax;
    int jmid;

    this->saveOccupationMatrix();

    this->doOccupationMatrix();

    jmin = getXMin();
    jmax = getXMax();

    jmid = ceil((jmax + jmin) / 2);

    return (-(jmid - N_BOX));
}

int MotionDetection::getXMin() const {
    int xmin = 2 * N_BOX;

    for (int i = 1; i <= N_BOX; i++)
        for (int j = 1; j <= 2 * N_BOX; j++) {
            if (o_cMatrix.get(i, j) == 5 && j < xmin)
                xmin = j;
        }
    
    return xmin;
}

int MotionDetection::getXMax() const {
    int xmax = 1;

    for (int i = 1; i <= N_BOX; i++)
        for (int j = 1; j <= 2 * N_BOX; j++) {
            if (o_cMatrix.get(i, j) == 5 && j > xmax)
                xmax = j;
        }
    return xmax;
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

/**
 * @return Verifico se na matriz não tenho mais elementos > 5
   se isso ocorre, é porque o objeto a ser perseguido
   foi perdido. Retorna true para isso.
 */
bool MotionDetection::itDisapear() {
    for (int i = 1; i <= N_BOX; i++) {
        for (int j = 1; j <= 2 * N_BOX; j++) {
            if (o_cMatrix(i, j) == 5)
                return false;
        }
    }
    return true;
}

/**
 * @return true se a matriz já foi alocada. false caso contrário.
 */
bool MotionDetection::isNotNullLastSeenMatrix() {
    return lastSeenMatrix.isAllocated();
}
