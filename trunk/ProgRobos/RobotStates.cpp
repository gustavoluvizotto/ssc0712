#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
using namespace std;

/*----------------------------------------------------------------------------*/

void SGlobalExample::Enter(Robot* pRobot) {
    cout << "Robot: Entrou no SGlobal" << endl;
}

void SGlobalExample::Execute(Robot* pRobot) {
    cout << "Robot: Executando o SGlobal" << endl;
}

void SGlobalExample::Exit(Robot* pRobot) {
    cout << "Robot: Saiu do SGlobal" << endl;
}

/*----------------------------------------------------------------------------*/

void S_Andando::Enter(Robot* pRobot) {
}

void S_Andando::Execute(Robot* pRobot) {
}

void S_Andando::Exit(Robot* pRobot) {
}

/*----------------------------------------------------------------------------*/
void S_Desvia::Enter(Robot* pRobot) {
}

void S_Desvia::Execute(Robot* pRobot) {
    
}

void S_Desvia::Exit(Robot* pRobot) {
}
