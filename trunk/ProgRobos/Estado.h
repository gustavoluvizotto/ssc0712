/* 
 * File:   Estado.h
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 24, 2013, 6:01 PM
 */

#ifndef ESTADO_H
#define	ESTADO_H
#include "Robo.h"

class Estado {
public:
    Estado();
    virtual ~Estado();
    virtual void execute(Robo* robo) = 0;  
};

#endif	/* ESTADO_H */

