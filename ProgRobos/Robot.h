#ifndef ROBOT_H
#define	ROBOT_H

#define THETA_MIN 0     // minimo angulo do laser
#define THETA_MAX 180   // 180, definido no sick.inc
#define LENGTH 3.0      // the max length of a data = 3m
#define THETA_MID (THETA_MAX+THETA_MIN)/2

#include "StateMachine.h"
#include "RobotStates.h"
#include "MotionDetection.h"
#include "Point.h"
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;
    PlayerClient* m_pRobot;
    Position2dProxy* m_pPp;
    RangerProxy* m_pRp;
    MotionDetection* m_pMD; //ponteiro pra classe MotionDetection

public:

    Robot() {
        m_pStateMachine = new StateMachine<Robot>(this);
        m_pStateMachine->SetGlobalState(SGlobalExample::Instance());
        m_pStateMachine->SetCurrentState(S_Andando::Instance());
        m_pRobot = new PlayerClient("localhost");
        m_pPp = new Position2dProxy(m_pRobot, 0);
        m_pRp = new RangerProxy(m_pRobot, 1);
        m_pPp->SetMotorEnable(true);
        m_pMD = new MotionDetection(this);
    }

    virtual ~Robot() {
        if (m_pMD) delete m_pMD;
        if (m_pRp) delete m_pRp;
        if (m_pPp) delete m_pPp;
        if (m_pRobot) delete m_pRobot;
        if (m_pStateMachine) delete m_pStateMachine;
    }

    void ReadSensors() {
        m_pRobot->Read();
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
        for (int i = 0; i < THETA_MAX; i++) {
            if (this->m_pRp->GetRange(i) < 0.5) {
                return true;
            }
        }
        return false;
    }

    void walkTurn(double speed, double angle) {
        this->m_pPp->SetSpeed(speed, angle);
    }

    MotionDetection* GetMD() {
        return m_pMD;
    }
};

#endif	/* ROBOT_H */
