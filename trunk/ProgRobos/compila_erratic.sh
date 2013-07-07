#!/bin/bash

#g++ -c *.cpp `pkg-config --libs --cflags playerc` -lm
#g++ -o programa *.o `pkg-config --libs --cflags playerc` -lm

g++ -c *.cpp -I/usr/local/include/player-3.0 -L/usr/local/lib -lplayerc -lm
g++ -o programa *.o -I/usr/local/include/player-3.0 -L/usr/local/lib -lplayerc -lm

