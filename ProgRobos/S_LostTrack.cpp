#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
#include "ToolBox.h"

using namespace std;

void S_LostTrack::Enter(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nEntrando no S_LostTrack" << endl;
#endif
}

void S_LostTrack::Execute(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nExecutando a S_LostTrack" << endl;
#endif
}

void S_LostTrack::Exit(Robot* pRobot) {
#ifdef DEBUG
    cout << "\nSaindo do S_LostTrack" << endl;
#endif
}