#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
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
}

void S_CollisionAvoidance::Exit(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nSaindo do S_CollisionAvoidance" << endl;
#endif
}