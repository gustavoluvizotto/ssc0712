#ifndef ROBOTSTATES_H
#define	ROBOTSTATES_H

#include "State.h"
class Robot;

class SGlobalExample : public State<Robot> {
private:

    SGlobalExample() {}
    virtual ~SGlobalExample() {}

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

    S_Andando() {}
    virtual ~S_Andando() {}

public:

    static S_Andando* Instance() {
        static S_Andando instance;
        return &instance;
    }

    virtual void Enter(Robot*);
    virtual void Execute(Robot*);
    virtual void Exit(Robot*);    
};

class S_Desvia : public State<Robot> {
private:

    S_Desvia() {}
    virtual ~S_Desvia() {}

public:

    static S_Desvia* Instance() {
        static S_Desvia instance;
        return &instance;
    }
    
    virtual void Enter(Robot*);
    virtual void Execute(Robot*);
    virtual void Exit(Robot*);
};

#endif	/* ROBOTSTATES_H */