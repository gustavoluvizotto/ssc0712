/* 
 * File:   Andar.cpp
 * Author: gustavo
 * 
 * Created on June 4, 2013, 10:05 PM
 */

#include "Andar.h"
#include "Robo.h"

Andar::Andar() {
}

Andar::~Andar() {
}

void Andar::execute(Robo* robo) {
    if (vaiBater(robo)) 
        desvia(robo);
    else
        anda(robo);
}

void Andar::desvia(Robo* robo) {
    robo->pp->SetSpeed(0.0,30.0);
}

void Andar::anda(Robo* robo) {
    robo->pp->SetSpeed(0.5, 0.0);
}

bool Andar::vaiBater(Robo* robo) {
    for (int i = 0; i < 180; i++) {
//        if (robo->rp[i] < 0.3)
        if (1 < 0.3)
            return true;
    }
    return false;
}
