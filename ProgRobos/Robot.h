#ifndef ROBOT_H
#define	ROBOT_H

#include "Parameters.h"
#include "StateMachine.h"
#include "RobotStates.h"
#include "MotionDetection.h"
#include "Point.h"
#include <libplayerc++/playerc++.h>
#include <cmath>

using namespace PlayerCc;

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;
    PlayerClient* m_pRobot;
    Position2dProxy* m_pPp;
    RangerProxy* m_pRp;
    MotionDetection* m_pMD; //ponteiro pra classe MotionDetection
    Matrix m_CurrentVisionMatrix; //representa a visão atual do Robô como uma matriz de ocupação
    Matrix m_PreviousVisionMatrix; //visão anterior
    Matrix m_LastSeenVisionMatrix; //visão "congelada" da última vez que o Prof. foi visto
    int ProfSizeOnMatrix; //estimativa do tamanho do Professor na matriz. É a qde de 5's detectados na primeira visão.

public:

    Robot() {
        m_pStateMachine = new StateMachine<Robot>(this);
        //        m_pStateMachine->SetGlobalState(S_Global::Instance());
        m_pStateMachine->SetCurrentState(S_InitialSetup::Instance());
        m_pRobot = new PlayerClient("localhost");
        m_pPp = new Position2dProxy(m_pRobot, 0);
        m_pRp = new RangerProxy(m_pRobot, 1);
        m_pPp->SetMotorEnable(true);
        m_CurrentVisionMatrix = Matrix(BOXES_LINES, BOXES_COLUMNS);
        m_PreviousVisionMatrix = Matrix(BOXES_LINES, BOXES_COLUMNS);
        m_LastSeenVisionMatrix = Matrix(BOXES_LINES, BOXES_COLUMNS);
        ProfSizeOnMatrix = 0;
        for (int i = 0; i <= 5; i++)
            ReadSensors(); //cria um delay. Bug do PlayerCC
        //        m_pMD = new MotionDetection(this);
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

    void Update() const {
        m_pStateMachine->Update();
    }

    void SetSpeed(const double XSpeed, const double YawSpeed) const {
        m_pPp->SetSpeed(XSpeed, YawSpeed);
    }

    double GetRange(uint32_t Index) const {
        return m_pRp->GetRange(Index);
    }

    //TODO Tem que remover essa função willHit() daqui. Colocar na ToolBox ou direto no estado

    bool willHit() const {
        for (int i = LASER_0DEG; i < LASER_180DEG; i++) {
            if (this->m_pRp->GetRange(i) < 0.8) {
                return true;
            }
        }
        return false;
    }

    MotionDetection* GetMD() const {
        return m_pMD;
    }

    Matrix& GetCurrentVisionMatrix() {
        return m_CurrentVisionMatrix;
    }

    Matrix& GetLastSeenVisionMatrix() {
        return m_LastSeenVisionMatrix;
    }

    Matrix& GetPreviousVisionMatrix() {
        return m_PreviousVisionMatrix;
    }

    int GetProfSizeOnMatrix() const {
        return ProfSizeOnMatrix;
    }

    void SetProfSizeOnMatrix(const int val) {
        assert(val >= 0);
        ProfSizeOnMatrix = val;
    }

    void IncreaseProfSizeOnMatrix() {
        ProfSizeOnMatrix++;
    }

};

#endif	/* ROBOT_H */