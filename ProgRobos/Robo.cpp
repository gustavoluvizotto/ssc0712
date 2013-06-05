/* 
 * File:   Robo.cpp
 * Author: Gustavo Luvizotto Cesar      - 6783544
 *         Leonardo Lourenço Crespilho  - 5124310 
 * Created on May 24, 2013, 6:02 PM
 */

#include "Robo.h"

/* inicializando o robo */
Robo::Robo(const char* host) {
    robot = new PlayerClient(host);
    rp = new RangerProxy(robot, 1);
    pp = new Position2dProxy(robot, 0);
}

/*
void Robo::trocaEstado(Estado* estado) {
    delete estadoAtual;
    estadoAtual = estado;
}

void Robo::atualizaEstado() {
    estadoAtual->execute(this);
}

void Robo::start() {
    robot->Read();
    trocaEstado(new Andar());
    while (true) 
        atualizaEstado();
    
}*/