#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include <unistd.h> //usleep()
#include "ToolBox.h"

using namespace std;

void S_CollisionAvoidance::Enter(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nEntrando no S_CollisionAvoidance" << endl;
#endif
}

void S_CollisionAvoidance::Execute(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nExecutando a S_CollisionAvoidance" << endl;
#endif
    /* não tratamos ainda. Tudo o que ela faz é esperar 5 segundos e volta para
     * S_Tracking. É suposto que alguém remova o obstáculo da frente do robô, ou
     o reposicione. */
    usleep(5000000); //aguarda 5s
    pRobot->GetFSM()->ChangeToState(S_Tracking::Instance());
}

void S_CollisionAvoidance::Exit(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nSaindo do S_CollisionAvoidance" << endl;
#endif
}