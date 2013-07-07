#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"

using namespace std;

void S_Global::Enter(Robot* pRobot) {
}

void S_Global::Execute(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nExecutando a S_Global" << endl;
#endif
    pRobot->ReadSensors();
    pRobot->GetPreviousVisionMatrix() = pRobot->GetVisionMatrix();
    ToolBox::FillVisionMatrix(pRobot);
}

void S_Global::Exit(Robot* pRobot) {
}