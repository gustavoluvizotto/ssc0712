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

/* Ao entrar nesse estado, o robo faz o mapeamento da regiao, caso seja a 
   primeira vez que esteja executando (condição inicial), ou busca pela 
   ultima posição onde se encontrava, carregando para a matriz de ocupação
   atual.
*/
void S_Andando::Enter(Robot* pRobot) {
    if (m_pMD == NULL)
        m_pMD->startOccupationMatrix(pRobot->getRangerProxy());
    else
        m_pMD->reachLastSeenPosition();
}

/* Ao executar esse estado, o robo deve verificar se vai bater, para que 
   possa salvar a ultima posição observada e então mudar de estado. Senão,
   irá ver o ângulo que deve girar para se posicionar frontalmente com o 
   objeto a ser seguido (o prof.).
*/
void S_Andando::Execute(Robot* pRobot) {
    if (m_pMD->itDisapear()) {
        pRobot->GetFSM()->ChangeToState(S_LostTrack::Instance());
    }
    if (pRobot->willHit()) {
        m_pMD->saveLastSeenPosition();
        this->Exit(pRobot);
    } else {
        int angle = m_pMD->getAngleToTurn(pRobot->getRangerProxy());
        pRobot->turn(angle);
        pRobot->walk(0.7);
    }
}

/* Saindo do estado andando e indo para o estado de desviar. Na verdade, o 
   estado de desviar deve ser global para que o robo sempre desvie dos 
   obstáculos. Essa verificação, entretanto, está sendo feita na execução
   deste mesmo estado (classe). Cabe a classe desviando para que ela desvie
   para uma posição que o robô não perca o tracking do objeto perseguido. 
   (é uma boa idéia???)...
*/
void S_Andando::Exit(Robot* pRobot) {
    pRobot->GetFSM()->ChangeToState(S_Desviando::Instance());
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

/*----------------------------------------------------------------------------*/

void S_LostTrack::Enter(Robot* pRobot){
}
void S_LostTrack::Execute(Robot* pRobot){
}
void S_LostTrack::Exit(Robot* pRobot){
}