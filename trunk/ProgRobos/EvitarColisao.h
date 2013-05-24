/* 
 * File:   EvitarColisao.h
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 24, 2013, 6:07 PM
 */

#ifndef EVITARCOLISAO_H
#define	EVITARCOLISAO_H

#include "Estado.h"
#include "Robo.h"


class EvitarColisao : public Estado{
public:
    EvitarColisao();
    EvitarColisao(const EvitarColisao& orig);
    virtual ~EvitarColisao();
    void execute(Robo* robo) {
        //outra implementacao
    }
private:

};

#endif	/* EVITARCOLISAO_H */

