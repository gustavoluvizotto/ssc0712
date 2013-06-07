#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
using namespace std;

void SGlobalExample::Enter(Robot* pRobot) {
    cout << "Robot: Entrou no SGlobal" << endl;
}

void SGlobalExample::Execute(Robot* pRobot) {
    cout << "Robot: Executando o SGlobal" << endl;
}

void SGlobalExample::Exit(Robot* pRobot) {
    cout << "Robot: Saiu do SGlobal" << endl;
}

void S1Example::Enter(Robot* pRobot) {
    cout << "Robot: Entrou no S1" << endl;
}

void S1Example::Execute(Robot* pRobot) {
    cout << "Robot: Executando o S1" << endl;
    pRobot->GetFSM()->ChangeToState(S2Example::Instance());
}

void S1Example::Exit(Robot* pRobot) {
    cout << "Robot: Saiu do S1" << endl;
}

void S2Example::Enter(Robot* pRobot) {
    cout << "Robot: Entrou no S2" << endl;
}

void S2Example::Execute(Robot* pRobot) {
    cout << "Robot: Executando o S2" << endl;
    pRobot->DecreaseVariavelExemplo();
    if (pRobot->isZeroVariavelExemplo())
        pRobot->GetFSM()->ChangeToState(S1Example::Instance());
}

void S2Example::Exit(Robot* pRobot) {
    cout << "Robot: Saiu do S2" << endl;
}

void Andando::Enter(Robot* pRobot) {
    cout << "Robot: Entrou no S2" << endl;
}

void Andando::Execute(Robot* pRobot) {
    cout << "Robot: Executando o S2" << endl;
    pRobot->DecreaseVariavelExemplo();
    if (pRobot->isZeroVariavelExemplo())
        pRobot->GetFSM()->ChangeToState(S1Example::Instance());
}

void Andando::Exit(Robot* pRobot) {
    cout << "Robot: Saiu do S2" << endl;
}

