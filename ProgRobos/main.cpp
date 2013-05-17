/* 
 * File:   main.cpp
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 17, 2013, 2:46 PM
 */

#include <iostream>
#include <cmath>
#include <libplayerc++/playerc++.h>
#include <cstdlib>
#include <cassert>

// parâmetros
const double VEL = 0.3; // velocidade do robô
const int FOV = 45; // campo de visão
const int fd = 0; // feixe da direita
const int fe = 180; // feixe da esquerda
const int ff = 90; // feixe da frente (meio)
const bool enable = true;
const bool disable = false;
const char *host = "localhost";
const int porta = 6660;

using namespace PlayerCc;
using namespace std;

int main(int argc, char **argv) {
    //assert(argc == 2);

    PlayerClient robot(host);
    RangerProxy rp(&robot, 1);
    Position2dProxy pp(&robot, 0);
    long double COS[181], SIN[181];
 
    robot.Read();
    for (int i = 0; i < 181; i++) {
        COS[i] = cos(i * M_PI / 180.0);
        SIN[i] = sin(i * M_PI / 180.0);
    }

    for (;;) {
        double speed = VEL;
        double x[181], y[181];
        int init = 0;

        robot.Read();
        cin >> init;
        for (int i=0; i<181; i++) {
            x[i] = rp[i]*cos(i*(M_PI/180.0));
            y[i] = rp[i]*sin(i*(M_PI/180.0));
            cout << x[i] << "\t" << y[i] << endl;
        }
    }

    return 0;
}
