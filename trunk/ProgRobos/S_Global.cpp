#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"

using namespace std;

void S_Global::Enter(Robot* pRobot) {
}

void S_Global::Execute(Robot* pRobot) {
    cout << "\nExecutando a S_Global" << endl;
    pRobot->ReadSensors();
    pRobot->GetPreviousVisionMatrix() = pRobot->GetCurrentVisionMatrix();
    pRobot->GetCurrentVisionMatrix().Clean();
    ToolBox::FillVisionMatrix(pRobot, pRobot->GetCurrentVisionMatrix(), false);
}

void S_Global::Exit(Robot* pRobot) {
}