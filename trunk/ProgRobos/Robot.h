#ifndef ROBOT_H
#define	ROBOT_H

#include "StateMachine.h"
#include "RobotStates.h"

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;

    //variáveis do Robô...
    int variavelExemplo;

public:

    Robot() {
        SetVariavelExemplo(3);
        m_pStateMachine = new StateMachine<Robot>(this);
        m_pStateMachine->SetGlobalState(SGlobalExample::Instance());
        m_pStateMachine->SetCurrentState(S1Example::Instance());
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
};

#endif	/* ROBOT_H */