#ifndef ROBOTSTATES_H
#define	ROBOTSTATES_H

#include "State.h"
#include "MotionDetection.h"

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

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
};

/*----------------------------------------------------------------------------*/

class S_Andando : public State<Robot> {
private:

    S_Andando() {
    }

    virtual ~S_Andando() {
    }

public:

    static S_Andando* Instance() {
        static S_Andando instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
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

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
};

/*----------------------------------------------------------------------------*/

class S_LostTrack : public State<Robot> {
private:

    S_LostTrack() {
    }

    virtual ~S_LostTrack() {
    }

public:

    static S_LostTrack* Instance() {
        static S_LostTrack instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
};

#endif	/* ROBOTSTATES_H */
