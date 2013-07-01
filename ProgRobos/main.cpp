/* 
 * File:   main.cpp
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 17, 2013, 2:46 PM
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>

#include "Robot.h"
#include "Matrix.h"
#include "Parameters.h"

using namespace std;

int main(int argc, char **argv) {

#ifdef DEBUG
    LASER_INFO;
#endif

    Robot* robot = new Robot();

    for (;;) {
        robot->Update();
    }

    delete robot;
    return 0;
}