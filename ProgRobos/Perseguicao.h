/* 
 * File:   Perseguicao.h
 * Author: gustavo
 *
 * Created on May 24, 2013, 6:04 PM
 */

#ifndef PERSEGUICAO_H
#define	PERSEGUICAO_H

#include "Estado.h"
#include "Robo.h"


class Perseguicao : public Estado {
public:
    Perseguicao();
    Perseguicao(const Perseguicao& orig);
    virtual ~Perseguicao();
    void execute(Robo* robo) {
        //implemento aqui
    }
private:

};

#endif	/* PERSEGUICAO_H */

