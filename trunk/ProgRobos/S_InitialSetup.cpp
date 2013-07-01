#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"

using namespace std;

void S_InitialSetup::Enter(Robot* pRobot) {
    cout << "\nEntrando no S_InitialSetup" << endl; //nunca é executada
}

void S_InitialSetup::Execute(Robot* pRobot) {
    cout << "\nExecutando a S_InitialSetup" << endl;
    pRobot->ReadSensors();
    ToolBox::FillVisionMatrix(pRobot, pRobot->GetCurrentVisionMatrix(), true);

    double DistanciaDoProfessor = ToolBox::GetProfDistance(pRobot->GetCurrentVisionMatrix());
    if (DistanciaDoProfessor >= 2) {
        pRobot->GetFSM()->SetGlobalState(S_Global::Instance());
        pRobot->GetFSM()->ChangeToState(S_Tracking::Instance());
    }
}

void S_InitialSetup::Exit(Robot* pRobot) {
    cout << "\nSaindo do S_InitialSetup" << endl;
}