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

class S1Example : public State<Robot> {
private:

    S1Example() {
    }

    virtual ~S1Example() {
    }

public:

    static S1Example* Instance() {
        static S1Example instance;
        return &instance;
    }

    virtual void Enter(Robot* miner);
    virtual void Execute(Robot* miner);
    virtual void Exit(Robot* miner);
};

class S2Example : public State<Robot> {
private:

    S2Example() {
    }

    virtual ~S2Example() {
    }

public:

    static S2Example* Instance() {
        static S2Example instance;
        return &instance;
    }

    virtual void Enter(Robot*);
    virtual void Execute(Robot*);
    virtual void Exit(Robot*);
};

class Andando : public State<Robot> {
private:

    Andando() {
    }

    virtual ~Andando() {
    }

public:

    static Andando* Instance() {
        static Andando instance;
        return &instance;
    }

    virtual void Enter(Robot*);
    virtual void Execute(Robot*);
    virtual void Exit(Robot*);
};

#endif	/* ROBOTSTATES_H */