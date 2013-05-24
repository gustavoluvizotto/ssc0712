/* 
 * File:   Robo.cpp
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 24, 2013, 6:02 PM
 */

#include "Robo.h"

Robo::Robo(char* host) {
    PlayerClient robot(host);
    RangerProxy rp(&robot, 1);
    Position2dProxy pp(&robot, 0);
}

Robo::Robo(const Robo& orig) {
}

Robo::~Robo() {
}

