/* 
 * File:   Robo.h
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 24, 2013, 6:02 PM
 */

#include <libplayerc++/playerc++.h>

#ifndef ROBO_H
#define	ROBO_H
class Estado;

using namespace PlayerCc;

class Robo {
public:
    Robo(const char* host);
    ~Robo();
    void trocaEstado(Estado* estadoAtual);
    void atualizaEstado();
    void start();
    
    PlayerClient* robot;
    RangerProxy* rp;
    Position2dProxy* pp;
    
private:
    Estado* estadoAtual;

};

#endif	/* ROBO_H */

