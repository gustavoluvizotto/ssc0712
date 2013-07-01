/* 
 * File:   CollisionAvoidance.cpp
 * Author: gustavo
 * 
 * Created on June 26, 2013, 11:14 AM
 */

#include "CollisionAvoidance.h"
#include "Parameters.h"

CollisionAvoidance::CollisionAvoidance(const Matrix& M, Robot* owner) {
    m_cMatrix = M;
}

CollisionAvoidance::~CollisionAvoidance() {
}

/**
 * @param owner = ponteiro para o robo
 * @return angulo que o robo deve virar pra evitar a colisao, para o lado 
 * correto para que nao perca o track do objetivo.
 */
double CollisionAvoidance::getAngleToAvoid(Robot* owner) {
    int xmin, xmax;
    xmin = getXMin(-1);
    xmax = getXMax(-1);
    if (xmin <= 24 || xmax <= 24) { // proximo pela esquerda
        //falta fazer esse método.
    }
    return 0.0;
}

/**
 * @param actualSpeed = velocidade atual do robo
 * @return velocidade com que o robo deve atuar
 */
double CollisionAvoidance::decreaseSpeed(double actualSpeed) {
    if (isCriticalLevel(5)) { // alterna entre ré e parado quando o objetivo 
        if (actualSpeed == 0) // vai se aproximando ao robo.
            return -0.1;
        return 0.0;
    }
    
    if (willCollideWithObjective())
        return actualSpeed/1.5;
    if (willCollideWithObstacle())
        return actualSpeed/1.5;
    
    return actualSpeed; // else...
}

/**
 * @return true se vai colidir com o obstaculo (-1). false cc. 30cm ou menos, 
 * risco de colisão
 */
bool CollisionAvoidance::willCollideWithObstacle() {
    if (getXMin(-1) <= 22 || getXMax(-1) <= 22) // proximo pela esquerda
        return true;
    if (getXMin(-1) >= 18 || getXMax(-1) >= 18) // proximo pela direita
        return true;
    if (getYMin(-1) <= 4 || getYMax(-1) <= 4) // proximo frontalmente
        return true;
    return false;
}

/**
 * @return true se vai colidir com objetivo (5). false cc. 60cm ou menos, risco
 * de colisao
 */
bool CollisionAvoidance::willCollideWithObjective() {
    if (getYMin(5) <= 4)
        return true;
    else
        return false;
}

/**
 * @return a maior linha da matriz que contenha o elemento ref
 */
int CollisionAvoidance::getYMax(const int ref) {
    int ymax = 1;

    for (int i = 1; i <= Y_BOXES; i++)
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_cMatrix.get(i, j) == ref && i > ymax)
                ymax = i;
        }

    return ymax;
}

/**
 * @return a maior coluna da matriz que contenha o elemento ref
 */
int CollisionAvoidance::getXMax(const int ref) {
    int xmax = 1;

    for (int i = 1; i <= Y_BOXES; i++)
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_cMatrix.get(i, j) == ref && j > xmax)
                xmax = j;
        }

    return xmax;
}

/**
 * @return a menor linha da matriz que contenha o elemento ref
 */
int CollisionAvoidance::getYMin(const int ref) {
    int ymin = Y_BOXES;

    for (int i = 1; i <= Y_BOXES; i++)
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_cMatrix.get(i, j) == ref && i < ymin)
                ymin = i;
        }

    return ymin;
}

/**
 * @return a menor coluna da matriz que contenha o elemento ref
 */
int CollisionAvoidance::getXMin(const int ref) {
    int xmin = 2 * Y_BOXES;

    for (int i = 1; i <= Y_BOXES; i++)
        for (int j = 1; j <= 2 * Y_BOXES; j++) {
            if (m_cMatrix.get(i, j) == ref && j < xmin)
                xmin = j;
        }

    return xmin;
}

/**
 * @return true se está no nível crítico de proximidade, false cc.
 */
bool CollisionAvoidance::isCriticalLevel(const int ref) {
    if (getYMin(ref) <= 2)
        return true;
    else
        return false;
}
