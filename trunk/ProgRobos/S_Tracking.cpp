#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"
#include <cmath>

using namespace std;

void S_Tracking::Enter(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nEntrando no S_Tracking" << endl;
#endif
}

void S_Tracking::Execute(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nExecutando a S_Tracking" << endl;
#endif

    Point<int> CMProf = ToolBox::GetCMOfFives(pRobot->GetVisionMatrix(), REFERENCIAL_ROBOT);
    double ProfDist = CMProf.module() * BOXSIZE; //não usei ToolBox::GetProfDistance por questões de performance
    double dist = ProfDist - DETECTION_DISTANCE; //desvio da distância ideal
    double DesvioAngular = -CMProf.argument(); //desvio angular entre o robô e o Professor
    double XSpeed = 0; //velocidade para frente
    double YawSpeed = 0; //velocidade de giro

    /* se for bater num obstáculo, vai pro estado S_CollisionAvoidance */
    if (ToolBox::WillHitOnObstacle(pRobot)) {
        pRobot->SetSpeed(0, 0);
        pRobot->GetFSM()->ChangeToState(S_CollisionAvoidance::Instance());
        return;
    }

    /* se perdeu rastro, vai para o estado S_LostTrack */
    if (ProfDist > MAXRANGE || CMProf.equals(0, 0)) {
        pRobot->SetSpeed(0, 0);
        pRobot->GetFSM()->ChangeToState(S_LostTrack::Instance());
        return;
    }

    /* tratamento do desvio angular:
     * - desvios entre -1 e 10 graus: não faz nada.
     * - caso contrário, corrige proporcionalmente ao desvio */
    if (abs(DesvioAngular) > DTOR(10))
        YawSpeed = 0.5 * DesvioAngular;


    /* tratamento da distância */

    //se MUITO perto, fica parado.
    if (ProfDist <= 0.5) {
        XSpeed = 0;
        YawSpeed = 0;
    }

    //se perto, afasta
    if (ProfDist > 0.5 && ProfDist < DETECTION_DISTANCE - 0.1)
        XSpeed = 0.8 * dist;

    //se longe, persegue
    if (ProfDist > DETECTION_DISTANCE + 0.1)
        XSpeed = 0.08 + 0.2 * dist;

#ifdef DEBUG
    PRINT(XSpeed);
    PRINT(YawSpeed);
#endif

    pRobot->SetSpeed(XSpeed, YawSpeed);
}

void S_Tracking::Exit(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nSaindo do S_Tracking" << endl;
#endif
}