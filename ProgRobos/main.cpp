/* 
 * File:   main.cpp
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 17, 2013, 2:46 PM
 */

#ifdef _CH_
#pragma package <opencv>
#endif
#define CV_NO_BACKWARD_COMPATIBILITY
#ifndef _EiC
#include "opencv/cv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#endif

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <opencv2/core/internal.hpp>

#include "Robot.h"
#include "Matrix.h"

// parâmetros
#define MAX_X 1000
#define MAX_Y 500
const double VEL = 0.3; // velocidade do robô
const int fd = 0; // feixe da direita
const int fe = 180; // feixe da esquerda
const int ff = 90; // feixe da frente (meio)

using namespace std;

int main(int argc, char **argv) {
    //assert(argc == 2);

    /*
    double COS[181]; //tabela de cossenos para evitar calcular toda hora
    double SIN[181]; //mesma coisa para o seno
    int i;
//    int init;
    bool_t livre;
    double X, Y;
    //    double x[181], y[181], x_antes[181], y_antes[181];
//    double theta;
//    double hyp;

    // OpenCV Variables
    char wndname[30] = "Sensor1";
    int line_type = CV_AA; // change it to 8 to see non-antialiased graphics
    CvPoint pt1, ptC = {(int) (MAX_X / 2), (int) (MAX_Y)}; //ptC = Centro
    IplImage* image;

    // Create a window
    image = cvCreateImage(cvSize(MAX_X, MAX_Y), 8, 3);
    cvNamedWindow(wndname, 1);
    cvZero(image);

    //popula as tabelas de seno e cosseno
    for (i = 0; i < 181; i++) {
        COS[i] = cos(i * M_PI / 180.0);
        SIN[i] = sin(i * M_PI / 180.0);
    }

    for (;;) {
        cin >> init;
        robot.Read();
        for (i = 0; i < 181; i++) {
            x_antes[i] = rp[i] * COS[i];
            y_antes[i] = rp[i] * SIN[i];
        }

        for (i = 0; i < 181; i++) {
            x[i] = rp[i] * COS[i];
            y[i] = rp[i] * SIN[i];
        }
        
        for (i = 0; i < 181; i++) {
            if (abs(x[i] - x_antes[i]) > 0.1) { // houve movimento
                hyp = sqrt(pow(x[i], 2) + pow(y[i], 2));
                theta = acos(x[i] / hyp); // turn no robo
            }
        } 

        //scan for free 0.5m in front of robot
        robot.Read();
        livre = true;
        cvZero(image);
        for (i = 0; i < 181; i++) {
            if (rp[i] < 0.5)
                livre = false;
            if (rp[i] < 7.8) {
                X = rp[i] * COS[i];
                Y = rp[i] * SIN[i];
                pt1 = {(int) ((MAX_X / 2) * (1 + X / 8)), (int) (MAX_Y * (1 - Y / 8))};
                cvCircle(image, pt1, 2, CV_RGB(255, 255, 255), 1, line_type, 0);
            }
        }
        cvCircle(image, ptC, (int) (MAX_X / 2), CV_RGB(255, 255, 255));
        cvShowImage(wndname, image);

        // if free, moves, otherwise turns
        if (livre)
            pp.SetSpeed(0.08, 0.0);
        else
            pp.SetSpeed(0.0, 0.08);
        cvWaitKey(10);
    }
     */

    //    Robo* robo = new Robo("localhost");
    //    robo->start();

    
    
    
    Matrix<double> m;
    return 0;
    
    
    
    Robot* robot = new Robot();
   
    for (;;) {
        robot->Update();
//        cout << endl;
    }

    return 0;
}
