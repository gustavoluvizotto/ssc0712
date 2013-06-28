#include "RobotStates.h"
#include "Robot.h"
#include <iostream>
using namespace std;

/* Busca pela ultima posição onde se encontrava, carregando para a matriz de
 * ocupação atual.
 */
void S_Andando::Enter(Robot* pRobot) {
    if (pRobot->GetMD()->isNotNullLastSeenMatrix())
        pRobot->GetMD()->reachLastSeenPosition();
}

/* Ao executar esse estado, o robo deve verificar se vai bater, para que 
   possa salvar a ultima posição observada e então mudar de estado. Senão,
   irá ver o ângulo que deve girar para se posicionar frontalmente com o 
   objeto a ser seguido (o prof.).
 */
void S_Andando::Execute(Robot* pRobot) {
    if (pRobot->GetMD()->isProfessorHasDisappeared()) {
        pRobot->GetMD()->saveLastSeenPosition();
        pRobot->GetFSM()->ChangeToState(S_LostTrack::Instance());
    }
    if (pRobot->willHit()) {
        pRobot->GetMD()->saveLastSeenPosition();
        pRobot->GetFSM()->ChangeToState(S_Desviando::Instance());
    } else {
        pRobot->SetSpeed(0.03, pRobot->GetMD()->getAngleToTurn());
    }
}

void S_Andando::Exit(Robot* pRobot) {
}

/*----------------------------------------------------------------------------*/

void S_Desviando::Enter(Robot* pRobot) {
}

void S_Desviando::Execute(Robot* pRobot) {
    if (pRobot->willHit()) pRobot->SetSpeed(0.1, pRobot->GetMD()->getAngleToTurn());
    else pRobot->GetFSM()->ChangeToState(S_Andando::Instance());
}

void S_Desviando::Exit(Robot* pRobot) {
}

/*----------------------------------------------------------------------------*/

void S_LostTrack::Enter(Robot* pRobot) {
}

void S_LostTrack::Execute(Robot* pRobot) {
}

void S_LostTrack::Exit(Robot* pRobot) {
}
