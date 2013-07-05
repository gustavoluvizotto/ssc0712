#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"

using namespace std;

void S_Tracking::Enter(Robot* pRobot) {
    cout << "\nEntrando no S_Tracking" << endl;
}

void S_Tracking::Execute(Robot* pRobot) {
}

void S_Tracking::Exit(Robot* pRobot) {
    cout << "\nSaindo do S_Tracking" << endl;
}