#ifndef ROBOTSTATES_H
#define	ROBOTSTATES_H

#include "State.h"
#include "MotionDetection.h"

class Robot;

class SGlobalExample : public State<Robot> {
public:
    SGlobalExample();
    virtual ~SGlobalExample();

    static SGlobalExample* Instance() {
        static SGlobalExample instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);

private:
};

/*----------------------------------------------------------------------------*/

class S_Andando : public State<Robot> {
public:
    S_Andando();
    virtual ~S_Andando();
    
    static S_Andando* Instance() {
        static S_Andando instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
    
private:
    MotionDetection m_pMD;
};

class S_Desviando : public State<Robot> {
public:
    S_Desviando();
    virtual ~S_Desviando();

    static S_Desviando* Instance() {
        static S_Desviando instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);

private:
};

/*----------------------------------------------------------------------------*/

class S_LostTrack : public State<Robot> {
public:
    S_LostTrack();
    virtual ~S_LostTrack();

    static S_LostTrack* Instance() {
        static S_LostTrack instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
    
private:
};

#endif	/* ROBOTSTATES_H */
