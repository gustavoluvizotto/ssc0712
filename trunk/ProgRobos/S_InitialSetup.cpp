#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"
#include "Parameters.h"

using namespace std;

void S_InitialSetup::Enter(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nEntrando no S_InitialSetup" << endl; //nunca é executada
#endif
}

void S_InitialSetup::Execute(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nExecutando a S_InitialSetup" << endl;
#endif
    pRobot->ReadSensors();
    ToolBox::FillVisionMatrix(pRobot, true);

    double DistanciaDoProfessor = ToolBox::GetProfDistance(pRobot->GetVisionMatrix());
#ifdef DEBUG
    PRINT(DistanciaDoProfessor);
#endif
    if (DistanciaDoProfessor >= DETECTION_DISTANCE && pRobot->GetProfSizeOnMatrix() >= 3) {
        pRobot->GetFSM()->SetGlobalState(S_Global::Instance());
        pRobot->GetFSM()->ChangeToState(S_Tracking::Instance());
    }
}

void S_InitialSetup::Exit(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nSaindo do S_InitialSetup" << endl;
#endif
}