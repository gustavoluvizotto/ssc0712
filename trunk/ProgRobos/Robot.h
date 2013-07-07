#ifndef ROBOT_H
#define	ROBOT_H

#include "Parameters.h"
#include "Matrix.h"
#include "StateMachine.h"
#include "RobotStates.h"
#include "Point.h"
#include <cmath>

#ifdef ROBO_SIMULADO
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
#elif defined ROBO_REAL
#include <libplayerc/playerc.h>
#endif

class Robot {
private:
    StateMachine<Robot>* m_pStateMachine;

#ifdef ROBO_SIMULADO
    PlayerClient* m_pRobot;
    Position2dProxy* m_pPp;
    RangerProxy* m_pRp;
#elif defined ROBO_REAL
    playerc_client_t* m_pRobot;
    playerc_position2d_t* m_pPp;
    playerc_laser_t* m_pLaser;
    playerc_ranger_t* m_pRp;
#endif

    Matrix m_VisionMatrix; //representa a visão atual do Robô como uma matriz de ocupação
    Matrix m_PreviousVisionMatrix; //visão imediatamente anterior. Poderia estar em ToolBox::FillVisionMatrix(), mas criamos aqui por questões de performance.
    Matrix m_LostTrackVisionMatrix; //visão "congelada" da última vez que o Prof. foi visto
    int ProfSizeOnMatrix; //estimativa do tamanho do Professor na matriz. É a qde de 5's colocados em m_VisionMatrix, quando no estado S_InitialSetup.

public:

    Robot() {
        m_pStateMachine = new StateMachine<Robot>(this);
        m_pStateMachine->SetCurrentState(S_InitialSetup::Instance());

#ifdef ROBO_SIMULADO

        m_pRobot = new PlayerClient("localhost");
        m_pPp = new Position2dProxy(m_pRobot, 0);
        m_pRp = new RangerProxy(m_pRobot, 1);
        m_pPp->SetMotorEnable(true);
        for (int i = 0; i <= 10; i++)
            ReadSensors(); //cria um delay. Bug do PlayerCC

#elif defined ROBO_REAL
        m_pRobot = playerc_client_create(NULL, "localhost", 6665);
        if (playerc_client_connect(m_pRobot) == 0) {
            COUT("PLAYERC_CLIENT_CONNECT() ERROR!");
            exit(-1);
        }

        m_pPp = playerc_position2d_create(m_pRobot, 0);
        if (playerc_position2d_subscribe(m_pPp, PLAYERC_OPEN_MODE) != 0) {
            COUT("PLAYERC_POSITION2D_SUBSCRIBE() ERROR!");
            exit(-1);
        }

        playerc_position2d_enable(m_pPp, 1);

        for (int i = 0; i < 10000; i++)
            COUT("Warming up...");

        m_pLaser = playerc_laser_create(m_pRobot, 0);
        if (playerc_laser_subscribe(m_pLaser, PLAYERC_OPEN_MODE)) {
            COUT("PLAYERC_LASER_SUBSCRIBE() ERROR!");
            exit(-1);
        }

        for (int i = 0; i < 10000; i++)
            COUT("Warming up laser...");

        for (int i = 0; i <= 10; i++)
            playerc_client_read(m_pRobot);
#endif

        m_VisionMatrix = Matrix(BOXES_ROWS, BOXES_COLUMNS);
        m_PreviousVisionMatrix = Matrix(BOXES_ROWS, BOXES_COLUMNS);
        m_LostTrackVisionMatrix = Matrix(BOXES_ROWS, BOXES_COLUMNS);
        ProfSizeOnMatrix = 0;
    }

    virtual ~Robot() {
#ifdef ROBO_SIMULADO
        if (m_pRp) delete m_pRp;
        if (m_pPp) delete m_pPp;
        if (m_pRobot) delete m_pRobot;
#endif
        if (m_pStateMachine) delete m_pStateMachine;
    }

    void ReadSensors() {
#ifdef ROBO_SIMULADO
        m_pRobot->Read();
#elif defined ROBO_REAL
        playerc_client_read(m_pRobot);
#endif
    }

    StateMachine<Robot>* GetFSM() const {
        return m_pStateMachine;
    }

    void Update() const {
        m_pStateMachine->Update();
    }

    void SetSpeed(double XSpeed, double YawSpeed) const {
        /* limita as velocidades em X e de giro, em 0.2m/s e 1volta/3s.
         * Estas restrições só são feitas aqui. A lógica que gera as velocidades
         * XSpeed e YawSpeed não as limita! Fizemos assim pra poder aumentar as
         * velocidades facilmente, caso necessário. */

        if (XSpeed > XSPEED_LIMIT)
            XSpeed = XSPEED_LIMIT;
        if (XSpeed < -XSPEED_LIMIT)
            XSpeed = -XSPEED_LIMIT;
        if (YawSpeed > YAWSPEED_LIMIT)
            YawSpeed = YAWSPEED_LIMIT;
        if (YawSpeed < -YAWSPEED_LIMIT)
            YawSpeed = -YAWSPEED_LIMIT;

#ifdef ROBO_SIMULADO
        m_pPp->SetSpeed(XSpeed, YawSpeed);
#elif defined ROBO_REAL
        playerc_position2d_set_cmd_vel(m_pPp, XSpeed, 0, YawSpeed, 1);
#endif
    }

    double GetRange(uint32_t Index) const {
#ifdef ROBO_SIMULADO
        return m_pRp->GetRange(Index);
#elif defined ROBO_REAL
        return m_pLaser->scan[Index][0];
#endif
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