#ifndef ROBOT_H
#define	ROBOT_H

#define THETA_MAX 180   // hokuyo is?
#define LENGTH 3.0      // the max length of a data

#include "StateMachine.h"
#include "RobotStates.h"
#include "Point.h"
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;
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
    
    RangerProxy getRangerProxy() {
        return this->m_pRp;
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

    bool willHit() {
        for (int i = 0; i < 180; i++) {
            if (this->m_pRp->GetRange(i) < 0.5) {
                //if ((*m_pRp)[i] < 0.5) //mesmo que: m_pRp->GetRange(i))
                return true;
            }
        }
        return false;
    }

    void walk(double speed) {
        this->m_pPp->SetSpeed(speed, 0);
    }

    void turn(int angle) {
        m_pPp->SetSpeed(0.0, angle);
    }
};

#endif	/* ROBOT_H */
