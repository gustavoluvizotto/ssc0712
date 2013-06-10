/* 
 * File:   Andar.cpp
 * Author: gustavo
 * 
 * Created on June 4, 2013, 10:05 PM
 */

#include "Andar.h"
#include "Robot.h"

Andar::Andar() {
}

Andar::~Andar() {
}

void Andar::execute(Robot* pRobot) {
    if (vaiBater(pRobot))
        desvia(pRobot);
    else
        anda(pRobot);
}

void Andar::desvia(Robot* pRobot) {
    pRobot->SetSpeed(0.0, 0.5);
}

void Andar::anda(Robot* pRobot) {
    pRobot->SetSpeed(0.5, 0.0);
}

bool Andar::vaiBater(Robot* pRobot) {
    for (int i = 0; i < 180; i++) {
        if (pRobot->GetRange(i) < 0.3)
            return true;
    }
    return false;
}