#include "RobotStates.h"
#include "Robot.h"
#include "MotionDetection.h"
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
S_Andando::S_Andando() {
    this->m_pMD = new MotionDetection();
}

void S_Andando::Enter(Robot* pRobot) {
    if (m_pMD == NULL)
        m_pMD->startOccupationMatrix(pRobot->getRangerProxy());
    else
        m_pMD->reachLastSeenPosition();
}

/*se vai bater, desvia, senão anda */
void S_Andando::Execute(Robot* pRobot) {
    if (pRobot->willHit()) {
        m_pMD->saveLastSeenPosition();
        pRobot->GetFSM()->ChangeToState(S_Desviando::Instance());
    } else {
        int angle = m_pMD->getAngleToTurn(pRobot->getRangerProxy());
        pRobot->turn(angle);
        pRobot->walk(0.7);
    }
}

void S_Andando::Exit(Robot* pRobot) {   // used for?
}

/*----------------------------------------------------------------------------*/

void S_Desviando::Enter(Robot* pRobot) {
}

/* Desvia enquanto estiver para bater. Depois anda */
void S_Desviando::Execute(Robot* pRobot) {
    if (pRobot->willHit()) pRobot->turn(10.0);
    else pRobot->GetFSM()->ChangeToState(S_Andando::Instance());
}

void S_Desviando::Exit(Robot* pRobot) {
}
