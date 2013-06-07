#ifndef ROBOT_H
#define	ROBOT_H

#include "StateMachine.h"
#include "RobotStates.h"

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;
    //variáveis do Robô...
    int variavelExemplo;
    PlayerClient robot("localhost");
    RangerProxy rp(&robot, 1);
    Position2dProxy pp(&robot, 0);
    
public:

    Robot() {
        SetVariavelExemplo(3);
        m_pStateMachine = new StateMachine<Robot>(this);
        m_pStateMachine->SetGlobalState(SGlobalExample::Instance());
        m_pStateMachine->SetCurrentState(S_Andando::Instance());
    }

    virtual ~Robot() {
        delete m_pStateMachine;
    }

    int GetVariavelExemplo() const {
        return variavelExemplo;
    }

    void SetVariavelExemplo(const int val) {
        variavelExemplo = val;
    }
    
    void DecreaseVariavelExemplo() {
        variavelExemplo--;
    }

    StateMachine<Robot>* GetFSM() {
        return m_pStateMachine;
    }

    void Update() {
        m_pStateMachine->Update();
    }
    
    bool isZeroVariavelExemplo() {
        return variavelExemplo <= 0;
    }
    
        
    bool vaiBater() {
        for (int i = 0; i < 180; i++)
            if (robot.)
    }
    
    void anda() {
        
    }
};

#endif	/* ROBOT_H */