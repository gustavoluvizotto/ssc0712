/* 
 * File:   Robo.h
 * Author: gustavo
 *
 * Created on May 24, 2013, 6:02 PM
 */

#include <libplayerc++/playerc++.h>

#ifndef ROBO_H
#define	ROBO_H

using namespace PlayerCc;

class Robo {
public:
    Robo(char* host);
    Robo(const Robo& orig);
    virtual ~Robo();
private:

};

#endif	/* ROBO_H */

