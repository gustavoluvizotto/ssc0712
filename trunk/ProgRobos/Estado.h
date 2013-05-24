/* 
 * File:   Estado.h
 * Author: gustavo
 *
 * Created on May 24, 2013, 6:01 PM
 */

#ifndef ESTADO_H
#define	ESTADO_H

#include "Robo.h"

class Estado {
public:
    Estado();
    Estado(const Estado& orig);
    virtual ~Estado();
    virtual void execute(Robo *robo)=0;
private:

};

#endif	/* ESTADO_H */

