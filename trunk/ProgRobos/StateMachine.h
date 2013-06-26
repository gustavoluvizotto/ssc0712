#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#include "State.h"
#include <cassert>
#include <cstddef>
#include <iostream>

template <class T>
class StateMachine {
private:

    T* m_pOwner;
    State<T>* m_pGlobalState;
    State<T>* m_pCurrentState;
    State<T>* m_pPreviousState;

public:

    StateMachine(T* owner) {
        m_pOwner = owner;
        m_pCurrentState = NULL;
        m_pGlobalState = NULL;
        m_pPreviousState = NULL;
    }

    virtual ~StateMachine() {
    }

    void SetCurrentState(State<T>* s) {
        m_pCurrentState = s;
    }

    void SetGlobalState(State<T>* s) {
        m_pGlobalState = s;
    }

    void SetPreviousState(State<T>* s) {
        m_pPreviousState;
    }

    void Update() const {
        if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
        if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
    }

    void ChangeToState(State<T>* pNewState) {
        assert(pNewState);
        m_pPreviousState = m_pCurrentState;
        m_pCurrentState->Exit(m_pOwner);
        m_pCurrentState = pNewState;
        m_pCurrentState->Enter(m_pOwner);
    }

    void RevertToPreviousState() {
        ChangeToState(m_pPreviousState);
    }

    State<T>* GetCurrentState() const {
        return m_pCurrentState;
    }

    State<T>* GetGlobalState() const {
        return m_pGlobalState;
    }

    State<T>* GetPreviousState() const {
        return m_pPreviousState;
    }
};

#endif	/* STATEMACHINE_H */