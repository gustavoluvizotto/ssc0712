#ifndef ROBOTSTATES_H
#define	ROBOTSTATES_H

#include "State.h"

class Robot;

class SGlobalExample : public State<Robot> {
private:

    SGlobalExample() {
    }

    virtual ~SGlobalExample() {
    }

public:

    static SGlobalExample* Instance() {
        static SGlobalExample instance;
        return &instance;
    }

    virtual void Enter(Robot* miner);
    virtual void Execute(Robot* miner);
    virtual void Exit(Robot* miner);
};

class S_Andando : public State<Robot> {
private:
    MotionDetection m_pMD;
public:
    S_Andando();
    virtual ~S_Andando();
    
    static S_Andando* Instance() {
        static S_Andando instance;
        return &instance;
    }

    virtual void Enter(Robot*);
    virtual void Execute(Robot*);
    virtual void Exit(Robot*);
};

class S_Desviando : public State<Robot> {
private:

    S_Desviando() {
    }

    virtual ~S_Desviando() {
    }

public:

    static S_Desviando* Instance() {
        static S_Desviando instance;
        return &instance;
    }

    virtual void Enter(Robot*);
    virtual void Execute(Robot*);
    virtual void Exit(Robot*);
};

#endif	/* ROBOTSTATES_H */