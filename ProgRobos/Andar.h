/* 
 * File:   Andar.h
 * Author: gustavo
 *
 * Created on June 4, 2013, 10:05 PM
 */

/*Criada apenas pra testar funcionamento do robo
 */

#ifndef ANDAR_H
#define	ANDAR_H

#include "State.h"
#include "Robot.h"

class Andar : public State<Robot> {
public:
    Andar();
    virtual ~Andar();
    bool vaiBater(Robot* pRobot);
    void execute(Robot* pRobot);
    void anda(Robot* pRobot);
    void desvia(Robot* pRobot);
private:

};

#endif	// ANDAR_H