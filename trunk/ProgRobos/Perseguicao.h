/* 
 * File:   Perseguicao.h
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 24, 2013, 6:04 PM
 */

#ifndef PERSEGUICAO_H
#define	PERSEGUICAO_H

#include "Estado.h"
#include "Robo.h"


class Perseguicao : public Estado {
public:
    Perseguicao();
    virtual ~Perseguicao();
    void execute(Robo* robo){}
    
private:

};

#endif	/* PERSEGUICAO_H */

