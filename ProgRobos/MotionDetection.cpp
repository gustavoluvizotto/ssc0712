/* 
 * File:   MotionDetection.cpp
 * Author: gustavo
 * 
 * Created on June 12, 2013, 10:50 AM
 */

#include "MotionDetection.h"
#include "Robot.h"
#include "Parameters.h"
#include <cmath>

MotionDetection::MotionDetection(Robot* owner) {
    if (owner != NULL) {
        threshold = 0;
        m_pOwner = owner;
        m_CurrentMatrix = Matrix(Y_BOXES, 2 * Y_BOXES); //já cria com zeros
        m_PreviousMatrix = Matrix(Y_BOXES, 2 * Y_BOXES); //já cria com zeros

        for (int i = 0; i <= 5; i++)
            m_pOwner->ReadSensors(); //cria um delay. Bug do PlayerCC
        startOccupationMatrix();
    }
}

MotionDetection::~MotionDetection() {
}

/**
 * A matriz de ocupação é a visão do Robô. É aproximadamente um retângulo de 6x3 m.
 * Qualquer coisa que aparecer nesse retângulo é levado em consideração pelo robô.
 * Todo o resto é ignorado.
 * 
 * Este método inicializa esta matriz com 5's, representando um objeto posicionado
 * frontalmenente ao robô, e desde que não tenha nada a menos de 1m de suas laterais.
 * Talvez tenhamos que mudar este valor.
 */
void MotionDetection::startOccupationMatrix() {
    Point<double> P;
    int x = 0, y = 0;
    int xold, yold;

    for (int i = LASER_0DEG; i <= LASER_180DEG; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= DETECTIONBOX_LENGTH) { // para os raios que estejam dentro da caixa imaginaria
//            P.polarToCartesian(m_pOwner->GetRange(i), i);
            xold = x;
            yold = y;
//            y = ceil(P.getY() / BOXSIZE);
            if (y > Y_BOXES) y = Y_BOXES;
            if (y == 0) y = 1;
//            x = Y_BOXES + ceil(P.getX() / BOXSIZE);
            if (x > 2 * Y_BOXES) x = 2 * Y_BOXES - 1;
            if (x == 0) x = 1;

            /* para todos os raios frontais (um metro pra esquera e um para a direita do robo)
               digo que valem 5 (para informar que é o objeto a ser seguido).
             */
            if (x <= (Y_BOXES + ceil(Y_BOXES / DETECTIONBOX_LENGTH)) || x >= (Y_BOXES - ceil(Y_BOXES / DETECTIONBOX_LENGTH))) {
                m_CurrentMatrix(y, x) = 5; // the frontal object to follow
                if (xold != x || yold != y) threshold++;
            } else
                m_CurrentMatrix(y, x) = -1; // obstacle of ambient
        }
    }
    m_CurrentMatrix.Print();
}

void MotionDetection::doOccupationMatrix() {
    int nfives = 0;
    Point<double> P;
    int x = 0, y = 0;
    int xold, yold;

    saveOccupationMatrix(); // saving actual informations

    m_CurrentMatrix.Clean(); // limpo a matriz

    for (int i = LASER_0DEG; i <= LASER_180DEG; i++) { // para todos os angulos
        if (m_pOwner->GetRange(i) <= DETECTIONBOX_LENGTH) { // para os raios que estejam dentro da caixa imaginaria
            //P.polarToCartesian(m_pOwner->GetRange(i), i);
            xold = x;
            yold = y;
            //y = ceil(P.getY() / BOXSIZE);
            if (y > Y_BOXES) y = Y_BOXES;
            if (y == 0) y = 1;
            //x = Y_BOXES + ceil(P.getX() / BOXSIZE);
            if (x > 2 * Y_BOXES) x = 2 * Y_BOXES;
            if (x == 0) x = 1;

            m_CurrentMatrix(y, x) = -1; // obstacle of ambient
            if ((isNextToFives(m_PreviousMatrix, y, x) || isNextToFives(m_CurrentMatrix, y, x)) && nfives <= threshold + 2) {
                m_CurrentMatrix(y, x) = 5;
                if (xold != x || yold != y) nfives++;
            }
        }
    }
    m_CurrentMatrix.Print();
}

/**percorre procurando se tem algum 5 ao redor de i,j
 * @param linha r e coluna c
 * @return true se está nas redondezas de um 5 e false cc.
 */
bool MotionDetection::isNextToFives(const Matrix& M, const int r, const int c) const {
    for (int k = -1; k <= 1; k++)
        for (int l = -1; l <= 1; l++) {
            if (r + k >= 1 && c + l >= 1 && r + k <= Y_BOXES && c + l <= 2 * Y_BOXES) // nao acesso indices nao definidos
                if (M.get(r + k, c + l) == 5)
                    return true;
        }
    return false;
}

double MotionDetection::getAngleToTurn() {
    doOccupationMatrix();

    double giro = (Y_BOXES - getXMiddle()) / 20.0;

    //dá uma segurada na velocidade de giro.
    if (giro > 1.0) giro = 1.0;
    else if (giro < -1.0) giro = -1.0;

    return giro;
}

int MotionDetection::getXMiddle() const {
    return (getXMax() + getXMin()) / 2;
}

int MotionDetection::getXMin() const {
    int xmin = 2 * Y_BOXES;

    for (int i = 1; i <= Y_BOXES; i++)
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_CurrentMatrix.get(i, j) == 5 && j < xmin)
                xmin = j;
        }

    return xmin;
}

int MotionDetection::getXMax() const {
    int xmax = 1;

    for (int i = 1; i <= Y_BOXES; i++)
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_CurrentMatrix.get(i, j) == 5 && j > xmax)
                xmax = j;
        }
    return xmax;
}

void MotionDetection::saveOccupationMatrix() {
    m_PreviousMatrix = m_CurrentMatrix;
}

void MotionDetection::saveLastSeenPosition() {
    m_lastSeenMatrix = m_CurrentMatrix;
}

void MotionDetection::reachLastSeenPosition() {
    m_CurrentMatrix = m_lastSeenMatrix;
}

/**
 * @return Verifico se na matriz não tenho mais elementos > 5
   se isso ocorre, é porque o objeto a ser perseguido
   foi perdido. Retorna true para isso.
 */
bool MotionDetection::isProfessorHasDisappeared() {
    for (int i = 1; i <= Y_BOXES; i++) {
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_CurrentMatrix(i, j) == 5)
                return false;
        }
    }
    return true;
}

/**
 * @return true se a matriz já foi alocada. false caso contrário.
 */
bool MotionDetection::isNotNullLastSeenMatrix() {
    return m_lastSeenMatrix.isAllocated();
}
