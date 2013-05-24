/* 
 * File:   PerdeuRastro.h
 * Author: gustavo
 *
 * Created on May 24, 2013, 6:09 PM
 */

#ifndef PERDEURASTRO_H
#define	PERDEURASTRO_H

#include "Estado.h"
#include "Robo.h"


class PerdeuRastro : public Estado{
public:
    PerdeuRastro();
    PerdeuRastro(const PerdeuRastro& orig);
    virtual ~PerdeuRastro();
    void execute(Robo* robo){
        //outra implementacao
    }
private:

};

#endif	/* PERDEURASTRO_H */

