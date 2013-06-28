#ifndef ROBOTSTATES_H
#define	ROBOTSTATES_H

#include "State.h"
#include "MotionDetection.h"

class Robot;

/**
 * Usado basicamente para realizar as tarefas que ocorrem em todo ciclo de update.
 * Inicialmente pensei me colocar o estado S_CollisionAvoidance como Global, mas
 * repensando achei que teria desvantagens e é melhor deixar S_CollisionAvoidance
 * como um estado não-global.
 */
class S_Global : public State<Robot> {
private:

    S_Global() {
    }

    virtual ~S_Global() {
    }

public:

    static S_Global* Instance() {
        static S_Global instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
};

/*----------------------------------------------------------------------------*/

/**
 * Setup inicial: Preenche a matriz de visão do Robô com o Professor. SÓ PODE SER EXECUTADO UMA ÚNICA VEZ.
 * visão de 2 por 3 metros (1m pra esquerda do robô, 1m pra direita, e 3m pra frente)
 */
class S_InitialSetup : public State<Robot> {
private:

    S_InitialSetup() {
    }

    virtual ~S_InitialSetup() {
    }

public:

    static S_InitialSetup* Instance() {
        static S_InitialSetup instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
};

/*----------------------------------------------------------------------------*/

/**
 * É o estado em que o robô efetivamente segue o Professor. Provavelmente é onde
 * o Robô passará a maior parte do tempo: perseguindo. Ele muda de estado caso aconteça
 * alguma anormalidade, como o Professor sair de vista, ou tiver que desviar de um obstáculo.
 * Caso contrário, continua seguindo.
 * Até mesmo se o Professor parar e o Robô alcançá-lo (ou o Professor vier de encontro ao
 * Robô, o que dá no mesmo), o estado não muda. A diferença é que o estado tem que detectar
 * essa situação e parar de andar, pois chegou no objetivo.
 * E se o Professor avançar em direção ao Robô, o Robô dá marcha ré, sempre olhando de frente
 * pro Professor. Mas perceba que o estado continua sendo este mesmo.
 * 
 * Situações de troca de estado:
 * 
 *  - desvio: Se tiver que desviar, vai pro estado S_CollisionAvoidance
 * 
 *  - perda do rastro: Se o Professor saiu do campo/matriz de visão, vai pro estado S_Losted
 */
class S_Tracking : public State<Robot> {
private:

    S_Tracking() {
    }

    virtual ~S_Tracking() {
    }

public:

    static S_Tracking* Instance() {
        static S_Tracking instance;
        return &instance;
    }

    virtual void Enter(Robot* pRobot);
    virtual void Execute(Robot* pRobot);
    virtual void Exit(Robot* pRobot);
};

/*----------------------------------------------------------------------------*/

/**
 * Nesse estado, o Robô faz um mix de desviar do obstáculo perseguindo o Professor.
 * Ou seja, não pode parar  de perseguir.
 * 
 * Exemplos de desvios/situações possíveis (com certeza existem diversas situações não contempladas):
 * 
 *  - o Professor está parcialmente bloqueado por um obstáculo. Neste caso, parte
 * da matriz de visão está marcada com -1, e parte com 5. O robô tem que desviar
 * para o lado em que há o 5, caso contrário ocorrerá perda de rastro com certeza.
 * É importante que, assim que o robô detectar que há um obstáculo entre ele e o
 * Prof, ele já vá para o lado do Prof, se afastando do obstáculo. Isso deve ser feito
 * porque se chegar perto do obstáculo, terá que fazer curvas fechadas e perderá
 * o rastro também.
 * 
 *  - o obstáculo entre o robô e o Professor não chegou a bloquear o Prof, mas o robô
 * corre o risco de raspar no obstáculo. Neste caso ele tem que desviar contra o obstáculo,
 * mas sem perder de vista o Professor.
 */
class S_CollisionAvoidance : public State<Robot> {
private:

    S_CollisionAvoidance() {
    }

    virtual ~S_CollisionAvoidance() {
    }

public:

    static S_CollisionAvoidance* Instance() {
        static S_CollisionAvoidance instance;
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

/*----------------------------------------------------------------------------*/

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
