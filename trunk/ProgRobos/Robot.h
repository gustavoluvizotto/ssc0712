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
    Matrix m_VisionMatrix; //representa a visão atual do Robô como uma matriz de ocupação
    Matrix m_PreviousVisionMatrix; //visão imediatamente anterior. Poderia estar em ToolBox::FillVisionMatrix(), mas criamos aqui por questões de performance.
    Matrix m_LostTrackVisionMatrix; //visão "congelada" da última vez que o Prof. foi visto
    int ProfSizeOnMatrix; //estimativa do tamanho do Professor na matriz. É a qde de 5's colocados em m_VisionMatrix, quando no estado S_InitialSetup.

public:

    Robot() {
        m_pStateMachine = new StateMachine<Robot>(this);
        //        m_pStateMachine->SetGlobalState(S_Global::Instance());
        m_pStateMachine->SetCurrentState(S_InitialSetup::Instance());
        m_pRobot = new PlayerClient("localhost");
        m_pPp = new Position2dProxy(m_pRobot, 0);
        m_pRp = new RangerProxy(m_pRobot, 1);
        m_pPp->SetMotorEnable(true);
        m_VisionMatrix = Matrix(BOXES_ROWS, BOXES_COLUMNS);
        m_PreviousVisionMatrix = Matrix(BOXES_ROWS, BOXES_COLUMNS);
        m_LostTrackVisionMatrix = Matrix(BOXES_ROWS, BOXES_COLUMNS);
        ProfSizeOnMatrix = 0;
        for (int i = 0; i <= 5; i++)
            ReadSensors(); //cria um delay. Bug do PlayerCC
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

    void SetSpeed(double XSpeed, double YawSpeed) const {
        //limita as velocidades em X e de giro, em 0.2m/s e 1volta/3s.
        if (XSpeed > 0.2)
            XSpeed = 0.2;
        if (XSpeed < -0.2)
            XSpeed = -0.2;
        if (YawSpeed > 2.0)
            YawSpeed = 2.0;
        if (YawSpeed < -2.0)
            YawSpeed = -2.0;

        m_pPp->SetSpeed(XSpeed, YawSpeed);
    }

    double GetRange(uint32_t Index) const {
        return m_pRp->GetRange(Index);
    }

    //TODO Tem que remover a função willHit() daqui. Colocar na ToolBox ou direto no estado

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

    Matrix& GetVisionMatrix() {
        return m_VisionMatrix;
    }

    Matrix& GetPreviousVisionMatrix() {
        return m_PreviousVisionMatrix;
    }

    Matrix& GetLostTrackVisionMatrix() {
        return m_LostTrackVisionMatrix;
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