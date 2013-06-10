#ifndef ROBOT_H
#define	ROBOT_H

#include "StateMachine.h"
#include "RobotStates.h"

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;
    int variavelExemplo;
    PlayerClient* m_pRobot;
    Position2dProxy* m_pPp;
    RangerProxy* m_pRp;

public:

    Robot() {
        m_pStateMachine = new StateMachine<Robot>(this);
        m_pStateMachine->SetGlobalState(SGlobalExample::Instance());
        m_pStateMachine->SetCurrentState(S_Andando::Instance());
        m_pRobot = new PlayerClient("localhost");
        m_pPp = new Position2dProxy(m_pRobot, 0);
        m_pRp = new RangerProxy(m_pRobot, 1);
        m_pPp->SetMotorEnable(true);
    }

    virtual ~Robot() {
        delete m_pStateMachine;
    }

    StateMachine<Robot>* GetFSM() const {
        return m_pStateMachine;
    }

    // Update na FSM, e talvez em outras variáveis do Robô, como Read() no sensor

    void Update() const {
        m_pRobot->Read();
        m_pStateMachine->Update();
    }

    void SetSpeed(const double XSpeed, const double YawSpeed) const {
        m_pPp->SetSpeed(XSpeed, YawSpeed);
    }
    
    double GetRange(uint32_t Index) const {
        return m_pRp->GetRange(Index);
    }

    bool vaiBater() {
        for (int i = 0; i < 180; i++) {
            if (m_pRp->GetRange(i))
            if ((*m_pRp)[i] < 0.9) //mesmo que: m_pRp->GetRange(i))
                return true;
        }
        return false;
    }

    void anda() {
        m_pPp->SetSpeed(0.5, 0);
    }

    void gira() {
        m_pPp->SetSpeed(0.0, 0.5);
    }
};

#endif	/* ROBOT_H */