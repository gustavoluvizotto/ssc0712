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

/*se vai bater, desvia, senão anda */
void S_Andando::Execute(Robot* pRobot) {
    if (pRobot->vaiBater())
        pRobot->GetFSM()->ChangeToState(S_Desviando::Instance());
    else
        pRobot->anda();
}

void S_Andando::Exit(Robot* pRobot) {
}

/*----------------------------------------------------------------------------*/

void S_Desviando::Enter(Robot* pRobot) {
}

/* Desvia enquanto estiver para bater. Depois anda */
void S_Desviando::Execute(Robot* pRobot) {
    if (pRobot->vaiBater()) pRobot->gira();
    else pRobot->GetFSM()->ChangeToState(S_Andando::Instance());
}

void S_Desviando::Exit(Robot* pRobot) {
}
